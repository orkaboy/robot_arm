#pragma once

namespace ARC {

class Motor {
public:
    virtual void Enable(bool enable) = 0;
    virtual void SetWheelMode() = 0;
    virtual void SetJointMode(float min, float max) = 0;

    virtual void JointSet(float angle) = 0;
    // 1.0 = full speed ccw, -1.0 = full speed cw
    virtual void WheelSet(float speed) = 0;

    virtual auto JointGet() const -> float = 0;

    bool JointIsDoneMoving(float goal) const;
};

}
