#pragma once

#include "vec.hpp"
#include <vector>

namespace ARC {

class FABRIK {
public:
    /* TODO add joint limits here */
    class Link {
    public:
        Link(vec3 pos, Real len, vec3 hingeAxis)
            : mPos(pos)
            , mLen(len)
            , mHingeAxis(hingeAxis)
        {}

        vec3 mHingeAxis{};
        vec3 mPos{};
        Real mLen{};
    };
    /* TODO orientation */
    using Goal = vec3;

    /* Assume scale is in m, tolerance is 0.01mm */
    FABRIK(const std::vector<Link>& links, Real tolerance = 0.00001, uint32_t iterLimit = 10);

    void SetPositions(const std::vector<vec3>& positions);

    std::vector<vec3> Calculate(const Goal& goal);
private:
    void Forward(const Goal& target);
    void Backward(const vec3& root);

    std::vector<Link> mLinks;
    Real mTolerance;
    uint32_t mIterLimit;
    Real mReach;
};

} // namespace ARC
