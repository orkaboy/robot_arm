#include "robot_lib.hpp"
#include "debug.hpp"
#include <fmt/core.h>

#include <fstream>
#include <sstream>
#include <string>

#include <ryml_std.hpp> // optional header. BUT when used, needs to be included BEFORE ryml.hpp
#include <ryml.hpp>

#include "mat.hpp"
#include "quat.hpp"
#include "bezier.hpp"

#include <thread>

namespace ARC {

constexpr auto PROTOCOL_VERSION = 1.0;
constexpr auto BAUDRATE = 1000000;
constexpr auto DEVICENAME = "/dev/ttyUSB0";

RobotArm::RobotArm(const std::string& config_file) {
    mDevice = DEVICENAME;

    struct JointConfig {
        JointConfig(uint32_t id_, std::string mode_, Real lim_min_, Real lim_max_)
            : id(id_), mode(mode_), lim_min(lim_min_), lim_max(lim_max_)
        {}
        uint32_t id;
        std::string mode;
        Real lim_min;
        Real lim_max;
    };
    std::vector<JointConfig> joints;

    {
        std::ifstream f(config_file.c_str());
        std::stringstream buffer;
        buffer << f.rdbuf();
        auto tree = ryml::parse_in_arena(ryml::to_csubstr(buffer.str()));

        bool debug = false;
        tree["debug"] >> debug;
        DEBUG(debug);
        tree["device"] >> mDevice;
        for(auto child : tree["links"].children()) {
            uint32_t id;
            std::string mode;
            Real lim_min, lim_max;
            child["id"] >> id;
            child["mode"] >> mode;
            child["lim_min"] >> lim_min;
            child["lim_max"] >> lim_max;
            joints.emplace_back(id, mode, lim_min, lim_max);
        }
    }
    
    mPortHandler = dynamixel::PortHandler::getPortHandler(mDevice.c_str());
    mPacketHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

    if(!mPortHandler->openPort()) {
        fmt::print("Failed to open port {}\n", mDevice);
        //return;
    }

    if(!mPortHandler->setBaudRate(BAUDRATE)) {
        fmt::print("Failed to set baudrate to {}\n", BAUDRATE);
        //return;
    }

    for(auto j : joints) {
        auto servo = new AX12A(mPortHandler, mPacketHandler, j.id);
        if(j.mode == "joint") {
            servo->SetJointMode(j.lim_min, j.lim_max);
        } else if(j.mode == "wheel") {
            servo->SetWheelMode(); // TODO set speed limits?
        }
        mJoints.push_back(servo);
    }

    mOK = true;
}

RobotArm::~RobotArm() {
    for(auto j : mJoints) {
        j->Enable(false);
        delete j;
    }
    mPortHandler->closePort();
}

auto RobotArm::SetJoints(const std::vector<Real>& drivers) -> bool {
    if(drivers.size() != mJoints.size()) {
        fmt::print("[RobotArm::SetJoints] Size of joints and drivers are not the same!\n");
        return false;
    }

    std::vector<std::pair<AX12A*, Real>> instructions;
    for(auto i = 0u; i < mJoints.size(); ++i) {
        auto j = mJoints[i];
        auto d = drivers[i];
        instructions.emplace_back(j, d);
    }

    AX12A::SyncJointMove(instructions);

    return true;
}

auto RobotArm::SetSpeed(Real speed) -> bool {
    speed = clamp(speed, 0.0, 1.0);
    const auto drivers = std::vector<Real>(mJoints.size(), speed);
    return SetSpeeds(drivers);
}

auto RobotArm::SetSpeeds(const std::vector<Real>& drivers) -> bool {
    if(drivers.size() != mJoints.size()) {
        fmt::print("[RobotArm::SetSpeeds] Size of joints and drivers are not the same!\n");
        return false;
    }

    std::vector<std::pair<AX12A*, Real>> instructions;
    for(auto i = 0u; i < mJoints.size(); ++i) {
        auto j = mJoints[i];
        auto d = drivers[i];
        instructions.emplace_back(j, d);
    }

    AX12A::SyncWheelMove(instructions);

    return true;
}

auto RobotArm::JointsIsDoneMoving(const std::vector<Real>& drivers) const -> bool {
    if(drivers.size() != mJoints.size()) {
        return false;
    }

    for(auto i = 0u; i < mJoints.size(); ++i) {
        auto joint = mJoints[i];
        auto goal = drivers[i];
        if(!joint->JointIsDoneMoving(goal)) {
            return false;
        }
    }
    return true;
}

void RobotArm::Enable(bool enable) {
    for(auto j : mJoints) {
        j->Enable(enable);
    }
}

void RobotArm::MoveToPos(const vec3& target, std::chrono::milliseconds time) {
    /* TEMP TODO Should be from current pos */
    const auto LIMB_LEN = 0.1; // In m
    const auto endEff = vec3(0,LIMB_LEN,LIMB_LEN);
    std::vector<FABRIK::Link> links = {
        {vec3(0,0,0), LIMB_LEN}, // Root
        {vec3(0,0,LIMB_LEN), LIMB_LEN},
        {endEff, 0.0} // End effector
    };
    // TEMP TODO
    constexpr auto steps = 10;
    const auto deltatime = time / steps;

    FABRIK ik(links);
    auto c = curve({endEff, endEff, target, target}); // TODO linear move first, but use cubic curve later

    for(auto i = 0u; i < steps; ++i) {
        auto t = static_cast<Real>(i) / (steps - 1);

        auto target_pos = c.sample(t);
        fmt::print("t[{}] = {}\n", i, target_pos.str());

        auto result = ik.Calculate(target_pos);
        /* TODO methods for converting to/from angles */


        // Wait
        std::this_thread::sleep_for(deltatime);
    }
}

} // namespace ARC
