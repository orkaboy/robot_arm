#include "fabrik.hpp"
#include <fmt/core.h>

namespace ARC {

FABRIK::FABRIK(const std::vector<Link>& links, Real tolerance, uint32_t iterLimit)
    : mLinks(links)
    , mTolerance(tolerance)
    , mIterLimit(iterLimit)
{
    mReach = 0.0;
    for(auto link : mLinks) {
        mReach += link.mLen;
    }
}

void FABRIK::SetPositions(const std::vector<vec3>& positions) {
    if(positions.size() != mLinks.size()) {
        fmt::print("[FABRIK::SetPositions] positions array has different length({}) from Links({})\n", positions.size(), mLinks.size());
        return;
    }

    for(auto i = 0u; i < positions.size(); ++i) {
        mLinks[i].mPos = positions[i];
    }
}

void FABRIK::Forward(const Goal& target) {
    /* Forward reaching stage */
    /* Set end effector pn to target */
    mLinks.back().mPos = target;
    /* Walk backwards through the chain */
    for(auto i = mLinks.size() - 2; i >= 0; --i) {
        auto link = mLinks[i];
        auto link2 = mLinks[i+1];
        /* Find the distance ri between the new joint position pi+1 and the joint pi */
        auto ri = (link2.mPos - link.mPos).norm();
        auto lambda = link.mLen / ri;
        /* Find the new joint position pi */
        link.mPos = link2.mPos * (1 - lambda) + link.mPos * lambda;
    }
}

void FABRIK::Backward(const vec3& root) {
    /* Backward reaching stage */
    /* Set root to its initial position */
    mLinks.front().mPos = root;
    /* Walk forwards through the chain */
    for(auto i = 0u; mLinks.size() - 1; ++i) {
        auto link = mLinks[i];
        auto link2 = mLinks[i+1];
        /* Find the distance ri between the new joint position pi and the joint pi+1 */
        auto ri = (link.mPos - link2.mPos).norm();
        auto lambda = link.mLen / ri;
        /* Find the new joint positions pi */
        link2.mPos = link.mPos * (1 - lambda) + link2.mPos * lambda;
    }
}

std::vector<vec3> FABRIK::Calculate(const Goal& target) {
    auto root = mLinks.front().mPos;
    /* Check distance between root and target */
    auto dist = (target - root).norm();
    /* Is the target within reach? */
    if(dist >= mReach) {
        for(auto i = 0u; i < mLinks.size() - 1; ++i) {
            auto link = mLinks[i];
            /* Find distance ri between target and the joint */
            auto ri = (target - link.mPos).norm();
            auto lambda = link.mLen / ri;
            /* Find the new joint position by projecting it towards the target */
            mLinks[i+1].mPos = link.mPos * (1 - lambda) + target * lambda;
        }
    }
    /* Target is reachable */
    else {
        /* Check distance between end effector pn and the target t is greater than the tolerance */
        auto diff = (target - mLinks.back().mPos).norm();
        auto iter = 0u;
        /* Iterate until we are inside the tolerance, or we have iterated the max number of times */
        while(diff > mTolerance && iter < mIterLimit) {
            Forward(target);
            Backward(root);
            diff = (target - mLinks.back().mPos).norm();
            ++iter;
        }
    }

    /* Return result */
    std::vector<vec3> ret;
    for(auto link : mLinks) {
        ret.emplace_back(link.mPos);
    }
    return ret;
}

} // namespace ARC
