#pragma once

#include <dynamixel_sdk/dynamixel_sdk.h>
#include "motor.hpp"

namespace ARC {

class AX12A : public Motor {
public:
    AX12A(
        dynamixel::PortHandler *portHandler,
        dynamixel::PacketHandler *packetHandler,
        uint32_t id
    );
private:
    dynamixel::PortHandler *mPortHandler{};
    dynamixel::PacketHandler *mPacketHandler{};
    uint32_t mID{};
};

}
