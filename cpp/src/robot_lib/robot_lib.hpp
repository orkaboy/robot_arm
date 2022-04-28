#pragma once

#include <dynamixel_sdk/dynamixel_sdk.h>
#include "ax-12a.hpp"
#include "fabrik.hpp"

#include <chrono>

namespace ARC {

class RobotArm {
public:
    RobotArm(const std::string& config_file);
    ~RobotArm();

    auto IsOK() -> bool { return mOK; };

    void Enable(bool enable);

    auto SetJoints(const std::vector<Real>& drivers) -> bool;
    auto JointsIsDoneMoving(const std::vector<Real>& drivers) const -> bool;

    auto SetSpeed(Real speed) -> bool;
    auto SetSpeeds(const std::vector<Real>& drivers) -> bool;

    void MoveToPos(const vec3& target, std::chrono::milliseconds time);
private:
    std::string mDevice;

    dynamixel::PortHandler *mPortHandler{};
    dynamixel::PacketHandler *mPacketHandler{};

    std::vector<AX12A*> mJoints;

    FABRIK* mIk = nullptr;
    bool mOK{};
};

} // namespace ARC
