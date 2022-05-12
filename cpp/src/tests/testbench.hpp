#pragma once

#include "vec.hpp" // for ARC::Real
#include <string>
#include <cassert>
#include <cmath>

constexpr ARC::Real HYSTERESIS = 0.0000001;
static void assert_float(ARC::Real f1, ARC::Real f2) {
    assert(f1 - HYSTERESIS < f2);
    assert(f1 + HYSTERESIS > f2);
}

enum class Status {
    Ok = 0,
    Err = 1,
};
