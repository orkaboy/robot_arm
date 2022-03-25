#include "ax-12a.hpp"
#include <fmt/core.h>

namespace ARC {

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

}
