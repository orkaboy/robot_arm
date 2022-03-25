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

    {
        std::ifstream f(config_file.c_str());
        std::stringstream buffer;
        buffer << f.rdbuf();
        auto tree = ryml::parse_in_arena(ryml::to_csubstr(buffer.str()));

        tree["device"] >> mDevice;
    }
    
    mPortHandler = dynamixel::PortHandler::getPortHandler(mDevice.c_str());
    mPacketHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
}

auto RobotArm::Init() -> bool {

    if(!mPortHandler->openPort()) {
        fmt::print("Failed to open port {}\n", mDevice);
        return false;
    }

    if(!mPortHandler->setBaudRate(BAUDRATE)) {
        fmt::print("Failed to set baudrate to {}\n", BAUDRATE);
        return false;
    }

    return true;
}

} // namespace ARC
