#pragma once

#include <dynamixel_sdk/dynamixel_sdk.h>
#include "motor.hpp"

#include <vector>
#include "vec.hpp"

namespace ARC {

class AX12A : public Motor {
public:
    AX12A(
        dynamixel::PortHandler *portHandler,
        dynamixel::PacketHandler *packetHandler,
        uint32_t id
    );

    static void SyncJointMove(const std::vector<std::pair<AX12A*, Real>>& positions);
    static void SyncWheelMove(const std::vector<std::pair<AX12A*, Real>>& speeds);

    void Enable(bool enable) override;
    void SetWheelMode() override;
    void SetJointMode(Real min, Real max) override;

    void JointSet(Real angle) override;
    void WheelSet(Real speed) override;

    auto JointGet() const -> Real override;
private:
    auto Write1ByteTxRx(uint32_t addr, uint8_t value) -> int;
    auto Write2ByteTxRx(uint32_t addr, uint16_t value) -> int;

    static auto AngleToPos(Real angle) -> uint16_t;
    static auto PosToAngle(uint16_t pos) -> Real;
    static auto SpeedToRaw(Real speed) -> uint16_t;

    dynamixel::PortHandler *mPortHandler{};
    dynamixel::PacketHandler *mPacketHandler{};
    uint32_t mID{};

    bool mWheelMode{};
};

}
