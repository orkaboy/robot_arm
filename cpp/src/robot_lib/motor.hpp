#pragma once

namespace ARC {

class Motor {
public:
    virtual void Enable(bool enable) = 0;
    virtual void SetWheelMode() = 0;
    virtual void SetJointMode(float min, float max) = 0;

    virtual void JointSet(float angle) = 0;
private:

};

}
