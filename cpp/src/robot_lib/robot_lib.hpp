#pragma once

#include <dynamixel_sdk/dynamixel_sdk.h>

namespace ARC {

class RobotArm {
public:
    RobotArm();

    auto Init() -> bool;
private:
    dynamixel::PortHandler *mPortHandler;
    dynamixel::PacketHandler *mPacketHandler;
};

} // namespace ARC
