#include "robot_lib.hpp"
#include <fmt/core.h>

#include <fstream>
#include <sstream>
#include <string>

#include <ryml_std.hpp> // optional header. BUT when used, needs to be included BEFORE ryml.hpp
#include <ryml.hpp>

namespace ARC {

constexpr auto PROTOCOL_VERSION = 1.0;
constexpr auto BAUDRATE = 1000000;
constexpr auto DEVICENAME = "/dev/ttyUSB0";

RobotArm::RobotArm(const std::string& config_file) {
    mDevice = DEVICENAME;

    struct JointConfig {
        JointConfig(uint32_t id_)
            : id(id_)
        {}
        uint32_t id;
    };
    std::vector<JointConfig> joints;

    {
        std::ifstream f(config_file.c_str());
        std::stringstream buffer;
        buffer << f.rdbuf();
        auto tree = ryml::parse_in_arena(ryml::to_csubstr(buffer.str()));

        tree["device"] >> mDevice;
        for(auto child : tree["links"].children()) {
            uint32_t id;
            child["id"] >> id;
            joints.emplace_back(id);
        }
    }
    
    mPortHandler = dynamixel::PortHandler::getPortHandler(mDevice.c_str());
    mPacketHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

    if(!mPortHandler->openPort()) {
        fmt::print("Failed to open port {}\n", mDevice);
        return;
    }

    if(!mPortHandler->setBaudRate(BAUDRATE)) {
        fmt::print("Failed to set baudrate to {}\n", BAUDRATE);
        return;
    }

    for(auto j : joints) {
        mJoints.emplace_back(new AX12A(mPortHandler, mPacketHandler, j.id));
    }

    mOK = true;
}

RobotArm::~RobotArm() {
    for(auto j : mJoints) {
        delete j;
    }
    mPortHandler->closePort();
}

bool RobotArm::SetJoints(std::vector<float> drivers) {
    if(drivers.size() != mJoints.size()) {
        return false;
    }

    std::vector<std::pair<AX12A*, float>> instructions;
    for(auto i = 0u; i < mJoints.size(); ++i) {
        auto j = mJoints[i];
        auto d = drivers[i];
        instructions.emplace_back(j, d);
    }

    AX12A::SyncJointMove(instructions);

    return true;
}

} // namespace ARC
