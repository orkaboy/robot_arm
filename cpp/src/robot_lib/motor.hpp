#pragma once

#include "vec.hpp"

namespace ARC {

class Motor {
public:
    virtual void Enable(bool enable) = 0;
    virtual void SetWheelMode() = 0;
    virtual void SetJointMode(Real min, Real max) = 0;

    virtual void JointSet(Real angle) = 0;
    // 1.0 = full speed ccw, -1.0 = full speed cw
    virtual void WheelSet(Real speed) = 0;

    virtual auto JointGet() const -> Real = 0;

    bool JointIsDoneMoving(Real goal) const;
};

}
