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

static void assert_vec3(ARC::vec3 v1, ARC::vec3 v2) {
    assert_float(v1.x, v2.x);
    assert_float(v1.y, v2.y);
    assert_float(v1.z, v2.z);
}

enum class Status {
    Ok = 0,
    Err = 1,
};
