#include "motor.hpp"

namespace ARC {

namespace Constants {

constexpr auto JointHysteresis = 0.05; // 3 degrees

}

bool Motor::JointIsDoneMoving(Real goal) const {
    auto cur = JointGet();
    if(cur > goal + Constants::JointHysteresis) { return false; }
    if(cur < goal - Constants::JointHysteresis) { return false; }
    return true;
}

}
