#include "fabrik.hpp"
#include "testbench.hpp"

enum class Tests {
    FABRIKLinkConstruct = 0,
    FABRIKConstruct = 1,
    FABRIKConstraints = 2,
    FABRIKForwardKinematics = 3,
};

auto FABRIKLinkConstruct() -> Status {
    {
        ARC::vec3 pos(1, 2, 3);
        ARC::Real len = 4;
        ARC::vec3 hingeAxis(1, 0, 0);
        ARC::FABRIK::Link link(pos, len, hingeAxis);
        assert_vec3(link.mPos, pos);
        assert_float(link.mLen, len);
        assert_vec3(link.mHingeAxis, hingeAxis);
        assert_float(link.mCWAngleLimit, -M_PI);
        assert_float(link.mCCWAngleLimit, M_PI);
    }

    {
        ARC::vec3 pos(5, 6, 7);
        ARC::Real len = 2;
        ARC::vec3 hingeAxis(0, 1, 2);
        ARC::Real CWAngleLimit = -M_PI / 2;
        ARC::Real CCWAngleLimit = M_PI / 3;
        ARC::FABRIK::Link link(pos, len, hingeAxis, CWAngleLimit, CCWAngleLimit);
        assert_vec3(link.mPos, pos);
        assert_float(link.mLen, len);
        assert_vec3(link.mHingeAxis, hingeAxis);
        assert_float(link.mCWAngleLimit, CWAngleLimit);
        assert_float(link.mCCWAngleLimit, CCWAngleLimit);
    }
    return Status::Ok;
}

auto FABRIKConstruct() -> Status {
    {
        const std::vector<ARC::FABRIK::Joint> joints = {
            {}
        };
        const std::vector<ARC::FABRIK::Link> links = {
            {{0,0,0}, 3, {0,0,1}},
            {{0,0,3}, 2, {1,0,0}},
        };
        ARC::FABRIK ik(joints, links);
    }

    {
        const std::vector<ARC::FABRIK::Joint> joints = {
            {}
        };
        const std::vector<ARC::FABRIK::Link> links = {
            {{0,0,0}, 2, {1,0,0}},
            {{0,2,0}, 3, {0,0,1}},
            {{3,2,0}, 1, {0,0,1}},
        };
        ARC::Real tolerance = 0.00001;
        uint32_t iterLimit = 10;
        ARC::FABRIK ik(joints, links, tolerance, iterLimit);
    }

    return Status::Err;
}

auto FABRIKConstraints() -> Status {
    const ARC::Real len = 2.0;
    const std::vector<ARC::FABRIK::Joint> joints = {
        {}
    };
    const std::vector<ARC::FABRIK::Link> links = {
        {{0,0,3}, len, {0,0,1}},
        {{len,0,3}, 0, {1,0,0}},
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
        {}
    };
    const std::vector<ARC::FABRIK::Link> links = {
        {{0,0,0}, 3, {0,0,1}},
        {{0,0,3}, 2, {1,0,0}},
        {{0,2,3}, 2, {0,0,1}},
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
