#include "fabrik.hpp"
#include <fmt/core.h>

#include "quat.hpp"

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
    for(int i = mLinks.size() - 2; i >= 0; --i) {
        auto& link = mLinks[i];
        auto link2 = mLinks[i+1];
        /* Calculate joint constraints */
        auto thisBoneOuterToInnerUV = (link.mPos - link2.mPos).normalize(); // Unit vector from outer to inner

        ARC::vec3 relativeHingeRotationAxis;
        if(i > 0) {
            auto& link3 = mLinks[i-1];
            auto orientation = vec3::toRotation(link.mPos, link3.mPos); // Direction of previous bone
            relativeHingeRotationAxis = link.mHingeAxis.rotate(orientation); // Rotate the hinge axis
        } else { // Basebone
            relativeHingeRotationAxis = link.mHingeAxis;
        }

        thisBoneOuterToInnerUV = thisBoneOuterToInnerUV.projOntoPlane(relativeHingeRotationAxis);

        // TODO rotation limits
        if(
            !ARC::approxEqual(link.mCWAngleLimit, -M_PI) &&
            !ARC::approxEqual(link.mCCWAngleLimit, M_PI)
        ) {

        }

        link.mPos = link2.mPos + thisBoneOuterToInnerUV * link.mLen;

        // OLD REMOVE
        // /* Find the distance ri between the new joint position pi+1 and the joint pi */
        // auto ri = (link2.mPos - link.mPos).norm();
        // auto lambda = link.mLen / ri;
        // /* Find the new joint position pi */
        // link.mPos = link2.mPos * (1 - lambda) + link.mPos * lambda;
    }
    fmt::print("Forward: {}\n", mLinks.back().mPos);
}

void FABRIK::Backward(const vec3& root) {
    /* Backward reaching stage */
    /* Set root to its initial position */
    mLinks.front().mPos = root;
    /* Walk forwards through the chain */
    for(auto i = 0u; i < mLinks.size() - 1; ++i) {
        auto link = mLinks[i];
        auto &link2 = mLinks[i+1];

        /* Calculate joint constraints */
        auto thisBoneInnerToOuterUV = (link2.mPos - link.mPos).normalize(); // Unit vector from inner to outer

        ARC::vec3 relativeHingeRotationAxis;
        if(i > 0) {
            auto& link3 = mLinks[i-1];
            auto orientation = vec3::toRotation(link3.mPos, link.mPos); // Direction of previous bone
            relativeHingeRotationAxis = link.mHingeAxis.rotate(orientation); // Rotate the hinge axis
        } else { // Basebone
            relativeHingeRotationAxis = link.mHingeAxis;
        }

        // TODO WIP
        fmt::print("  relativeHingeRotationAxis: {}\n", relativeHingeRotationAxis);
        fmt::print("  thisBoneInnerToOuterUV: {}\n", thisBoneInnerToOuterUV);
        thisBoneInnerToOuterUV = thisBoneInnerToOuterUV.projOntoPlane(relativeHingeRotationAxis);
        fmt::print("  proj thisBoneInnerToOuterUV: {}\n", thisBoneInnerToOuterUV);

        // TODO rotation limits
        if(
            !ARC::approxEqual(link.mCWAngleLimit, -M_PI) &&
            !ARC::approxEqual(link.mCCWAngleLimit, M_PI)
        ) {
            /*
            Vec3f relativeHingeReferenceAxis = m.times( thisBoneJoint.getHingeReferenceAxis() ).normalise();
            
            // Get the signed angle (about the hinge rotation axis) between the hinge reference axis and the hinge-rotation aligned bone UV
            // Note: ACW rotation is positive, CW rotation is negative.
            float signedAngleDegs = Vec3f.getSignedAngleBetweenDegs(relativeHingeReferenceAxis, thisBoneInnerToOuterUV, relativeHingeRotationAxis);
            
            // Make our bone inner-to-outer UV the hinge reference axis rotated by its maximum clockwise or anticlockwise rotation as required
            if (signedAngleDegs > acwConstraintDegs)
            {	
                thisBoneInnerToOuterUV = Vec3f.rotateAboutAxisDegs(relativeHingeReferenceAxis, acwConstraintDegs, relativeHingeRotationAxis).normalise();		        		
            }
            else if (signedAngleDegs < cwConstraintDegs)
            {	
                thisBoneInnerToOuterUV = Vec3f.rotateAboutAxisDegs(relativeHingeReferenceAxis, cwConstraintDegs, relativeHingeRotationAxis).normalise();			        		
            }
            */
        }

        link2.mPos = link.mPos + thisBoneInnerToOuterUV * link.mLen;

        // OLD REMOVE
        // /* Find the distance ri between the new joint position pi and the joint pi+1 */
        // auto ri = (link.mPos - link2.mPos).norm();
        // auto lambda = link.mLen / ri;
        // /* Find the new joint positions pi */
        // link2.mPos = link.mPos * (1 - lambda) + link2.mPos * lambda;
    }
    fmt::print("Backward: {}\n", mLinks.back().mPos);
}

std::vector<vec3> FABRIK::Calculate(const Goal& target) {
    auto root = mLinks.front().mPos;
    /* Check distance between root and target */
    auto dist = (target - root).norm();
    /* Is the target within reach? */
    // OLD REMOVE, doesn't work with constraints!
//    if(dist >= mReach) {
//        // TODO Must obey constraints!
//        for(auto i = 0u; i < mLinks.size() - 1; ++i) {
//            auto link = mLinks[i];
//            /* Find distance ri between target and the joint */
//            auto ri = (target - link.mPos).norm();
//            auto lambda = link.mLen / ri;
//            /* Find the new joint position by projecting it towards the target */
//            mLinks[i+1].mPos = link.mPos * (1 - lambda) + target * lambda;
//        }
//    }
//    /* Target is reachable */
//    else {
        /* Check distance between end effector pn and the target t is greater than the tolerance */
        auto diff = (target - mLinks.back().mPos).norm();
        auto iter = 0u;
        /* Iterate until we are inside the tolerance, or we have iterated the max number of times */
        while(diff > mTolerance && iter < mIterLimit) {
            Forward(target);
            Backward(root);
            diff = (target - mLinks.back().mPos).norm();
            ++iter;
            fmt::print("Iter {}, diff = {}\n", iter, diff);
        }
//    }

    /* Return result */
    std::vector<vec3> ret;
    for(auto link : mLinks) {
        ret.emplace_back(link.mPos);
    }
    return ret;
}

FABRIK::Goal FABRIK::ForwardKinematics() const {
    FABRIK::Goal endEff = mLinks.back().mPos;
    for(const auto& link: mLinks) {
        // TODO orientation
    }
    return endEff;
}

} // namespace ARC
