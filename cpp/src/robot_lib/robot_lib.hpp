#pragma once

#include <dynamixel_sdk/dynamixel_sdk.h>
#include "ax-12a.hpp"

namespace ARC {

class RobotArm {
public:
    RobotArm(const std::string& config_file);
    ~RobotArm();

    auto IsOK() -> bool { return mOK; };

    bool SetJoints(std::vector<float> drivers);
private:
    std::string mDevice;

    dynamixel::PortHandler *mPortHandler{};
    dynamixel::PacketHandler *mPacketHandler{};

    std::vector<AX12A*> mJoints;

    bool mOK{};
};

} // namespace ARC
