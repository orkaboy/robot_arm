#include "ax-12a.hpp"
#include <fmt/core.h>

#include <cmath>

namespace ARC {

namespace REG {
    // Control table of EEPROM
    constexpr uint32_t ModelNumber          =  0;
    constexpr uint32_t FirmwareVersion      =  2;
    constexpr uint32_t ID                   =  3;
    constexpr uint32_t Baudrate             =  4;
    constexpr uint32_t ReturnDelayTime      =  5;
    constexpr uint32_t CWAngleLimit         =  6;
    constexpr uint32_t CCWAngleLimit        =  8;
    constexpr uint32_t TemperatureLimit     = 11;
    constexpr uint32_t MinVoltageLimit      = 12;
    constexpr uint32_t MaxVoltageLimit      = 13;
    constexpr uint32_t MaxTorque            = 14;
    constexpr uint32_t StatusReturnLevel    = 16;
    constexpr uint32_t AlarmLED             = 17;
    constexpr uint32_t Shutdown             = 18;
    // Control table of RAM
    constexpr uint32_t TorqueEnable         = 24;
    constexpr uint32_t LED                  = 25;
    constexpr uint32_t CWComplianceMargin   = 26;
    constexpr uint32_t CCWComplianceMargin  = 27;
    constexpr uint32_t CWComplianceSlope    = 28;
    constexpr uint32_t CCWComplianceSlope   = 29;
    constexpr uint32_t GoalPosition         = 30;
    constexpr uint32_t MovingSpeed          = 32;
    constexpr uint32_t TorqueLimit          = 34;
    constexpr uint32_t PresentPosition      = 36;
    constexpr uint32_t PresentSpeed         = 38;
    constexpr uint32_t PresentLoad          = 40;
    constexpr uint32_t PresentVoltage       = 42;
    constexpr uint32_t PresentTemperature   = 43;
    constexpr uint32_t Registered           = 44;
    constexpr uint32_t Moving               = 46;
    constexpr uint32_t Lock                 = 47;
    constexpr uint32_t Punch                = 48;
}

namespace Constants {
    // Positions for GoalPosition/PresentPosition
    constexpr uint32_t PosMidpoint          = 512;
    constexpr uint32_t PosMin               = 0;
    constexpr uint32_t PosMax               = 1023;

    constexpr float    AngleMin             = -5*M_PI/6;
    constexpr float    AngleMax             =  5*M_PI/6;

    constexpr size_t   GoalPositionSize     = 2;
    constexpr uint16_t MaxSpeed             = 1023;
    constexpr uint16_t CWOffset             = 1024;
}


AX12A::AX12A(
    dynamixel::PortHandler *portHandler,
    dynamixel::PacketHandler *packetHandler,
    uint32_t id
)
    : mPortHandler(portHandler)
    , mPacketHandler(packetHandler)
    , mID(id)
{
    uint8_t dxl_error{};
    uint16_t dxl_model_number{};
    auto dxl_comm_result = mPacketHandler->ping(mPortHandler, mID, &dxl_model_number, &dxl_error);
    if(dxl_comm_result != COMM_SUCCESS) {
        fmt::print("{}\n", mPacketHandler->getTxRxResult(dxl_comm_result));
    } else if(dxl_error != 0) {
        fmt::print("{}\n", mPacketHandler->getTxRxResult(dxl_error));
    } else {
        fmt::print("[ID:{:03}] ping succeeded. Dynamixel model number: {}\n", mID, dxl_model_number);
    }
}

auto AX12A::Write1ByteTxRx(uint32_t addr, uint8_t value) -> int {
    uint8_t dxl_error{};
    return mPacketHandler->write1ByteTxRx(mPortHandler, mID, addr, value, &dxl_error);
}

auto AX12A::Write2ByteTxRx(uint32_t addr, uint16_t value) -> int {
    uint8_t dxl_error{};
    return mPacketHandler->write2ByteTxRx(mPortHandler, mID, addr, value, &dxl_error);
}

void AX12A::Enable(bool enable) {
    Write1ByteTxRx(REG::TorqueEnable, enable);
}

void AX12A::SetWheelMode() {
    /* Servo can move freely using REG::MovingSpeed */
    /* In this mode, 0-1023 is move CCW (0 = stop, 1023 = full output) */
    /* 1024-2047 is move CW (1024 = stop, 2047 = full output) */
    Write2ByteTxRx(REG::CWAngleLimit, 0);
    Write2ByteTxRx(REG::CCWAngleLimit, 0);
    mWheelMode = true;
}

auto AX12A::AngleToPos(float angle) -> uint16_t {
    if(angle < Constants::AngleMin) { angle = Constants::AngleMin; }
    if(angle > Constants::AngleMax) { angle = Constants::AngleMax; }
    return Constants::PosMin + (Constants::PosMax - Constants::PosMin) * (angle - Constants::AngleMin) / (Constants::AngleMax - Constants::AngleMin);
}

auto AX12A::PosToAngle(uint16_t pos) -> float {
    if(pos < Constants::PosMin) { pos = Constants::PosMin; }
    if(pos > Constants::PosMax) { pos = Constants::PosMax; }
    return Constants::AngleMin + (Constants::AngleMax - Constants::AngleMin) * (static_cast<float>(pos) - Constants::PosMin) / (Constants::PosMax - Constants::PosMin);
}

void AX12A::SetJointMode(float min, float max) {
    /* Servo speed is set with REG::MovingSpeed 0..1023 (0 = max speed) */
    /* Set position with REG::GoalPosition */
    uint16_t cw = AngleToPos(min);
    uint16_t ccw = AngleToPos(max);
    Write2ByteTxRx(REG::CWAngleLimit, cw);
    Write2ByteTxRx(REG::CCWAngleLimit, ccw);
    mWheelMode = false;
}

void AX12A::JointSet(float angle) {
    auto pos = AngleToPos(angle);
    Write2ByteTxRx(REG::GoalPosition, pos);
}

void AX12A::SyncJointMove(const std::vector<std::pair<AX12A*, float>>& positions) {
    if(positions.empty()) {
        return;
    }

    auto servo = positions[0].first;
    dynamixel::GroupSyncWrite groupSyncWrite(
        servo->mPortHandler,
        servo->mPacketHandler,
        REG::GoalPosition,
        Constants::GoalPositionSize
    );

    uint8_t param_goal_pos[2];
    for(auto it : positions) {
        auto servo = it.first;
        auto pos = AngleToPos(it.second);

        param_goal_pos[0] = DXL_LOBYTE(pos);
        param_goal_pos[1] = DXL_HIBYTE(pos);

        groupSyncWrite.addParam(servo->mID, param_goal_pos);
    }

    groupSyncWrite.txPacket();
}


// 1.0 = full speed ccw, -1.0 = full speed cw
void AX12A::WheelSet(float speed) {
    /* In Wheel mode, servo can move freely using REG::MovingSpeed */
    /* 0-1023 is move CCW (0 = stop, 1023 = full output) */
    /* 1024-2047 is move CW (1024 = stop, 2047 = full output) */
    uint16_t value = 0;
    if(speed < 0.0) {
        value = Constants::CWOffset;
        speed = -speed;
    }
    if(speed > 1.0) {
        speed = 1.0;
    }
    value += speed * Constants::MaxSpeed;

    Write2ByteTxRx(REG::MovingSpeed, value);
}

auto AX12A::JointGet() const -> float {
    uint8_t dxl_error{};
    uint16_t position{};
    auto dxl_comm_result = mPacketHandler->read2ByteTxRx(mPortHandler, mID, REG::PresentPosition, &position, &dxl_error);
    return PosToAngle(position);
}

}
