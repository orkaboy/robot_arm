#include "fabrik.hpp"
#include "testbench.hpp"

enum class Tests {
    FABRIKLinkConstruct = 0,
    FABRIKConstruct = 1,
    FABRIKConstraints = 2,
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
        const std::vector<ARC::FABRIK::Link> links = {
            {{0,0,0}, 3, {0,0,1}},
            {{0,0,3}, 2, {1,0,0}},
        };
        ARC::FABRIK ik(links);
    }
    
    {
        const std::vector<ARC::FABRIK::Link> links = {
            {{0,0,0}, 2, {1,0,0}},
            {{0,2,0}, 3, {0,0,1}},
            {{3,2,0}, 1, {0,0,1}},
        };
        ARC::Real tolerance = 0.00001;
        uint32_t iterLimit = 10;
        ARC::FABRIK ik(links, tolerance, iterLimit);
    }

    return Status::Err;
}

auto FABRIKConstraints() -> Status {
    const std::vector<ARC::FABRIK::Link> links = {
        {{0,0,0}, 3, {0,0,1}},
        {{0,0,3}, 2, {1,0,0}},
    };
    ARC::FABRIK ik(links);

    return Status::Err;
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
    default:
        break;
    }

    return static_cast<int>(ret);
}
