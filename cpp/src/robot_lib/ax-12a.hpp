#pragma once

#include <dynamixel_sdk/dynamixel_sdk.h>
#include "motor.hpp"

#include <vector>

namespace ARC {

class AX12A : public Motor {
public:
    AX12A(
        dynamixel::PortHandler *portHandler,
        dynamixel::PacketHandler *packetHandler,
        uint32_t id
    );

    static void SyncJointMove(const std::vector<std::pair<AX12A*, float>>& positions);
    static void SyncWheelMove(const std::vector<std::pair<AX12A*, float>>& speeds);

    void Enable(bool enable) override;
    void SetWheelMode() override;
    void SetJointMode(float min, float max) override;

    void JointSet(float angle) override;
    void WheelSet(float speed) override;

    auto JointGet() const -> float override;
private:
    auto Write1ByteTxRx(uint32_t addr, uint8_t value) -> int;
    auto Write2ByteTxRx(uint32_t addr, uint16_t value) -> int;

    static auto AngleToPos(float angle) -> uint16_t;
    static auto PosToAngle(uint16_t pos) -> float;
    static auto SpeedToRaw(float speed) -> uint16_t;

    dynamixel::PortHandler *mPortHandler{};
    dynamixel::PacketHandler *mPacketHandler{};
    uint32_t mID{};

    bool mWheelMode{};
};

}
