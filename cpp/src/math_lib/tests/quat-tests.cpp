#include "quat.hpp"
#include "mat.hpp"
#include "testbench.hpp"

enum class Tests {
    QuatConstruct = 0,
    QuatStr = 1,
    QuatAdd = 2,
    QuatSub = 3,
    QuatMul = 4,
    QuatScalarMul = 5,
    QuatNorm = 6,
    QuatNormalize = 7,
    QuatUnitnorm = 8,
    QuatInverse = 9,
    QuatSlerp = 10,
    QuatNlerp = 11,
    QuatToMat = 12,
};

auto QuatConstruct() -> Status {
    return Status::Err;
}

auto QuatStr() -> Status {
    return Status::Err;
}

auto QuatAdd() -> Status {
    return Status::Err;
}

auto QuatSub() -> Status {
    return Status::Err;
}

auto QuatMul() -> Status {
    return Status::Err;
}

auto QuatScalarMul() -> Status {
    return Status::Err;
}

auto QuatNorm() -> Status {
    return Status::Err;
}

auto QuatNormalize() -> Status {
    return Status::Err;
}

auto QuatUnitnorm() -> Status {
    return Status::Err;
}

auto QuatInverse() -> Status {
    return Status::Err;
}

auto QuatSlerp() -> Status {
    return Status::Err;
}

auto QuatNlerp() -> Status {
    return Status::Err;
}

auto QuatToMat() -> Status {
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
    case Tests::QuatConstruct:
        ret = QuatConstruct(); break;
    case Tests::QuatStr:
        ret = QuatStr(); break;
    case Tests::QuatAdd:
        ret = QuatAdd(); break;
    case Tests::QuatSub:
        ret = QuatSub(); break;
    case Tests::QuatMul:
        ret = QuatMul(); break;
    case Tests::QuatScalarMul:
        ret = QuatScalarMul(); break;
    case Tests::QuatNorm:
        ret = QuatNorm(); break;
    case Tests::QuatNormalize:
        ret = QuatNormalize(); break;
    case Tests::QuatUnitnorm:
        ret = QuatUnitnorm(); break;
    case Tests::QuatInverse:
        ret = QuatInverse(); break;
    case Tests::QuatSlerp:
        ret = QuatSlerp(); break;
    case Tests::QuatNlerp:
        ret = QuatNlerp(); break;
    case Tests::QuatToMat:
        ret = QuatToMat(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
