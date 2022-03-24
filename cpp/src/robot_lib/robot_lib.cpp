#include "robot_lib.hpp"
#include <fmt/core.h>

namespace ARC {

constexpr auto PROTOCOL_VERSION = 1.0;
constexpr auto BAUDRATE = 1000000;
constexpr auto DEVICENAME = "/dev/ttyUSB0";

RobotArm::RobotArm()
    : mPortHandler(dynamixel::PortHandler::getPortHandler(DEVICENAME))
    , mPacketHandler(dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION))
{
}

auto RobotArm::Init() -> bool {
    if(!mPortHandler->openPort()) {
        fmt::print("Failed to open port {}\n", DEVICENAME);
        return false;
    }

    if(!mPortHandler->setBaudRate(BAUDRATE)) {
        fmt::print("Failed to set baudrate to {}\n", BAUDRATE);
        return false;
    }

    return true;
}

} // namespace ARC
