#include "motor.hpp"

namespace ARC {

namespace Constants {

constexpr auto JointHysteresis = 0.025; // 1.5 degrees

}

bool Motor::IsDoneMoving(float goal) const {
    auto cur = JointGet();
    if(cur > goal + Constants::JointHysteresis) { return false; }
    if(cur < goal - Constants::JointHysteresis) { return false; }
    return true;
}

}
