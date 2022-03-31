// 150,750;200,700;250,900;0,1023;0,1023;0,1023
#include <cstdlib>
#include <unistd.h>
#include <cstdint>
#include <cmath>

#include <fmt/core.h>

using Real = double;

namespace Constants {
    // Positions for GoalPosition/PresentPosition
    constexpr uint32_t PosMidpoint          = 512;
    constexpr uint32_t PosMin               = 0;
    constexpr uint32_t PosMax               = 1023;

    constexpr Real     AngleMin             = -5*M_PI/6;
    constexpr Real     AngleMax             =  5*M_PI/6;

    constexpr uint16_t MaxSpeed             = 1023;
    constexpr uint16_t CWOffset             = 1024;

    constexpr size_t   GoalPositionSize     = 2;
    constexpr size_t   MovingSpeedSize      = 2;
}

auto PosToAngle(uint16_t pos) -> Real {
    if(pos < Constants::PosMin) { pos = Constants::PosMin; }
    if(pos > Constants::PosMax) { pos = Constants::PosMax; }
    return Constants::AngleMin + (Constants::AngleMax - Constants::AngleMin) * (static_cast<Real>(pos) - Constants::PosMin) / (Constants::PosMax - Constants::PosMin);
}

#include <vector>

auto main(int argc, char* argv[]) -> int {
    std::vector<std::pair<uint16_t, uint16_t>> lims = {
        {150,750},
        {200,700},
        {250,900},
        {0,1023},
        {0,1023},
        {0,1023},
    };
    for(auto& it : lims) {
        auto low = PosToAngle(it.first);
        auto hi = PosToAngle(it.second);
        fmt::print("Lims: {}, {}\n", low, hi);
    }
    return 0;
}
