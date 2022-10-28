#include "fabrik.hpp"
#include "testbench.hpp"

enum class Tests {
    FABRIKLinkConstruct = 0,
    FABRIKJointConstruct = 1,
    FABRIKConstruct = 2,
    FABRIKConstraints = 3,
    FABRIKForwardKinematics = 4,
};

auto FABRIKLinkConstruct() -> Status {
    {
        ARC::Real len = 4;
        ARC::FABRIK::Link link(len);
        assert_float(link.mLen, len);
        assert(link.mOriginJointID == 0);
        assert(link.mTargetJointID == 0);
    }

    {
        ARC::Real len = 2;
        int originID = 1;
        int targetID = 2;
        ARC::FABRIK::Link link(len, originID, targetID);
        assert_float(link.mLen, len);
        assert(link.mOriginJointID == originID);
        assert(link.mTargetJointID == targetID);
    }
    return Status::Ok;
}

auto FABRIKJointConstruct() -> Status {
    {
        ARC::vec3 pos(1, 2, 3);
        ARC::vec3 hingeAxis(1, 0, 0);
        ARC::FABRIK::Joint joint(pos, hingeAxis);
        assert_vec3(joint.mPos, pos);
        assert_vec3(joint.mHingeAxis, hingeAxis);
        assert_float(joint.mCWAngleLimit, -M_PI);
        assert_float(joint.mCCWAngleLimit, M_PI);
    }

    {
        ARC::vec3 pos(5, 6, 7);
        ARC::Real len = 2;
        ARC::vec3 hingeAxis(0, 1, 2);
        ARC::Real CWAngleLimit = -M_PI / 2;
        ARC::Real CCWAngleLimit = M_PI / 3;
        ARC::FABRIK::Joint joint(pos, hingeAxis, CWAngleLimit, CCWAngleLimit);
        assert_vec3(joint.mPos, pos);
        assert_vec3(joint.mHingeAxis, hingeAxis);
        assert_float(joint.mCWAngleLimit, CWAngleLimit);
        assert_float(joint.mCCWAngleLimit, CCWAngleLimit);
    }
    return Status::Ok;
}

auto FABRIKConstruct() -> Status {
    {
        const std::vector<ARC::FABRIK::Joint> joints = {
            {{0,0,0}, {0,0,1}},
            {{0,0,3}, {1,0,0}},
            {{0,2,3}, {0,0,1}}, /* End effector */
        };
        const std::vector<ARC::FABRIK::Link> links = {
            {3, /* JointIDs */ 0, 1},
            {2, /* JointIDs */ 1, 2},
        };
        ARC::FABRIK ik(joints, links);
    }

    {
        const std::vector<ARC::FABRIK::Joint> joints = {
            {{0,0,0}, {1,0,0}},
            {{0,2,0}, {0,0,1}},
            {{3,2,0}, {0,0,1}},
            {{3,2,1}, {0,0,1}}, /* End effector */
        };
        const std::vector<ARC::FABRIK::Link> links = {
            {2, /* JointIDs */ 0, 1},
            {3, /* JointIDs */ 1, 2},
            {1, /* JointIDs */ 2, 3},
        };
        ARC::Real tolerance = 0.00001;
        uint32_t iterLimit = 10;
        ARC::FABRIK ik(joints, links, tolerance, iterLimit);
    }

    /* TODO: Implement more tests */
    return Status::Err;
}

auto FABRIKConstraints() -> Status {
    const ARC::Real len = 2.0;
    const std::vector<ARC::FABRIK::Joint> joints = {
        {{0,0,3}, {0,0,1}},
        {{len,0,3}, {1,0,0}},
    };
    const std::vector<ARC::FABRIK::Link> links = {
        {len, /* JointIDs */ 0, 1},
    };
    ARC::FABRIK ik(joints, links);

    std::vector<ARC::FABRIK::Goal> goals = {
        {0.001, 0.0, 1.0},
        {4.0, 2.0, 1.0},
        {2.0, 4.0, 6.0},
        {0.001, 0.0, 3.0},
        {-4.0, -2.0, 2.0},
        {2.0, -1.0, 10.0},
    };
    for(const auto& g : goals) {
        ik.Calculate(g);
        ARC::FABRIK::Goal result = ik.ForwardKinematics();
        assert_float(result.z, 3.0);
        ARC::vec3 base(0.0, 0.0, 3.0);
        ARC::Real dist = (result - base).norm();
        // fmt::print("target: {} res: {}, {}\n", g, result, dist);
        assert_float(dist, len);
    }

    return Status::Ok;
}

auto FABRIKForwardKinematics() -> Status {
    const std::vector<ARC::FABRIK::Joint> joints = {
        {{0,0,0}, {0,0,1}},
        {{0,0,3}, {1,0,0}},
        {{0,2,3}, {0,0,1}},
    };
    const std::vector<ARC::FABRIK::Link> links = {
        {3, /* JointIDs */ 0, 1},
        {2, /* JointIDs */ 1, 2},
    };
    const ARC::FABRIK ik(joints, links);

    ARC::FABRIK::Goal goal = ik.ForwardKinematics();

    assert_vec3(goal, {0,2,3});

    return Status::Ok;
}

auto main(int argc, char* argv[]) -> int {
    if(argc != 2) {
        return static_cast<int>(Status::Err);
    }
    auto test = static_cast<Tests>(std::stoi(argv[1]));

    Status ret = Status::Err;

    switch (test)
    {
    case Tests::FABRIKLinkConstruct:
        ret = FABRIKLinkConstruct(); break;
    case Tests::FABRIKJointConstruct:
        ret = FABRIKJointConstruct(); break;
    case Tests::FABRIKConstruct:
        ret = FABRIKConstruct(); break;
    case Tests::FABRIKConstraints:
        ret = FABRIKConstraints(); break;
    case Tests::FABRIKForwardKinematics:
        ret = FABRIKForwardKinematics(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
