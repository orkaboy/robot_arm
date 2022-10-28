#pragma once

#include "vec.hpp"
#include <vector>

namespace ARC {

class FABRIK {
public:
    /* TODO add joint limits here */
    class Link {
    public:
        Link(vec3 pos, Real len, vec3 hingeAxis, Real CWAngleLimit = -M_PI, Real CCWAngleLimit = M_PI, int originJointID = 0, int targetJointID = 0)
            : mPos(pos)
            , mLen(len)
            , mHingeAxis(hingeAxis)
            , mCWAngleLimit(CWAngleLimit)
            , mCCWAngleLimit(CCWAngleLimit)
            , mOriginJointID(originJointID)
            , mTargetJointID(targetJointID)
        {}

        vec3 mHingeAxis{};
        vec3 mPos{};
        Real mLen{};
        Real mCWAngleLimit{};
        Real mCCWAngleLimit{};
        int mOriginJointID{};
        int mTargetJointID{};
    };
    /* TODO orientation */
    using Goal = vec3;

    class Joint {
    public:
        Joint(vec3 pos, vec3 hingeAxis, Real CWAngleLimit = -M_PI, Real CCWAngleLimit = M_PI)
            : mPos(pos)
            , mHingeAxis(hingeAxis)
            , mCWAngleLimit(CWAngleLimit)
            , mCCWAngleLimit(CCWAngleLimit)
        {}

        vec3 mPos{};
        vec3 mHingeAxis{};
        Real mCWAngleLimit{};
        Real mCCWAngleLimit{};
    };

    /* Assume scale is in m, tolerance is 0.01mm */
    FABRIK(const std::vector<Link>& links, Real tolerance = 0.00001, uint32_t iterLimit = 10);

    void SetPositions(const std::vector<vec3>& positions);

    std::vector<vec3> Calculate(const Goal& goal);

    Goal ForwardKinematics() const;
private:
    void Forward(const Goal& target);
    void Backward(const vec3& root);

    std::vector<Link> mLinks;
    Real mTolerance;
    uint32_t mIterLimit;
    Real mReach;
};

} // namespace ARC
