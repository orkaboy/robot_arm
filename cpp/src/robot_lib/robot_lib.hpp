#pragma once

#include <dynamixel_sdk/dynamixel_sdk.h>

namespace ARC {

class RobotArm {
public:
    RobotArm(const std::string& config_file);
    ~RobotArm();

    auto IsOK() -> bool { return mOK; };
private:
    std::string mDevice;

    dynamixel::PortHandler *mPortHandler{};
    dynamixel::PacketHandler *mPacketHandler{};

    bool mOK{};
};

} // namespace ARC
