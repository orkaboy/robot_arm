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
    QuatToMatIdentity = 12,
    QuatToMat2 = 13,
};

auto QuatConstruct() -> Status {
    ARC::quat q1;
    assert_float(q1.s, 0.0);
    assert_float(q1.v.x, 0.0);
    assert_float(q1.v.y, 0.0);
    assert_float(q1.v.z, 0.0);
    ARC::quat q2(1,2,3,4);
    assert_float(q2.s, 1);
    assert_float(q2.v.x, 2);
    assert_float(q2.v.y, 3);
    assert_float(q2.v.z, 4);
    ARC::quat q3(1, {2,3,4});
    assert_float(q3.s, 1);
    assert_float(q3.v.x, 2);
    assert_float(q3.v.y, 3);
    assert_float(q3.v.z, 4);
    ARC::quat q4(q3);
    assert_float(q4.s, 1);
    assert_float(q4.v.x, 2);
    assert_float(q4.v.y, 3);
    assert_float(q4.v.z, 4);
    ARC::quat q5 = q3;
    assert_float(q5.s, 1);
    assert_float(q5.v.x, 2);
    assert_float(q5.v.y, 3);
    assert_float(q5.v.z, 4);
    return Status::Ok;
}

auto QuatStr() -> Status {
    ARC::quat q1;
    assert(q1.str() == "[0, (0 0 0)]");
    ARC::quat q2(1, 2, 3, 4);
    assert(q2.str() == "[1, (2 3 4)]");
    return Status::Ok;
}

auto QuatAdd() -> Status {
    ARC::quat q1(1, 2, 3, 4);
    ARC::quat q2(5, 6, 7, 8);
    ARC::quat q3 = q1 + q2;
    assert_float(q3.s, 6);
    assert_float(q3.v.x, 8);
    assert_float(q3.v.y, 10);
    assert_float(q3.v.z, 12);
    q3 = q2 + q1;
    assert_float(q3.s, 6);
    assert_float(q3.v.x, 8);
    assert_float(q3.v.y, 10);
    assert_float(q3.v.z, 12);
    q3 += q1;
    assert_float(q3.s, 7);
    assert_float(q3.v.x, 10);
    assert_float(q3.v.y, 13);
    assert_float(q3.v.z, 16);
    return Status::Ok;
}

auto QuatSub() -> Status {
    ARC::quat q1(5, 6, 7, 8);
    ARC::quat q2(4, 3, 2, 1);
    ARC::quat q3 = q1 - q2;
    assert_float(q3.s, 1);
    assert_float(q3.v.x, 3);
    assert_float(q3.v.y, 5);
    assert_float(q3.v.z, 7);
    q3 -= q2;
    assert_float(q3.s, -3);
    assert_float(q3.v.x, 0);
    assert_float(q3.v.y, 3);
    assert_float(q3.v.z, 6);
    return Status::Ok;
}

auto QuatMul() -> Status {
    return Status::Err;
}

auto QuatScalarMul() -> Status {
    ARC::quat q1(1, 2, 3, 4);
    ARC::quat q2 = q1 * 3;
    assert_float(q2.s, 3);
    assert_float(q2.v.x, 6);
    assert_float(q2.v.y, 9);
    assert_float(q2.v.z, 12);
    q2 *= 2;
    assert_float(q2.s, 6);
    assert_float(q2.v.x, 12);
    assert_float(q2.v.y, 18);
    assert_float(q2.v.z, 24);
    return Status::Ok;
}

auto QuatNorm() -> Status {
    ARC::quat q1(2, 3, 4, 5);
    // sqrt(4 + 9 + 16 + 25) = sqrt(54)
    ARC::Real norm = q1.norm();
    assert_float(norm, std::sqrt(54));
    // 4 + 9 + 16 + 25 = 54
    ARC::Real norm2 = q1.norm2();
    assert_float(norm2, 54);
    return Status::Ok;
}

auto QuatNormalize() -> Status {
    ARC::quat q0;
    ARC::quat q0_normalized = q0.normalize();
    assert_float(q0_normalized.s, 0);
    assert_float(q0_normalized.v.x, 0);
    assert_float(q0_normalized.v.y, 0);
    assert_float(q0_normalized.v.z, 0);

    ARC::quat q1(2, 3, 4, 5);
    ARC::Real norm = q1.norm();
    ARC::quat q1_normalized = q1.normalize();
    assert_float(q1_normalized.s, 2 / norm);
    assert_float(q1_normalized.v.x, 3 / norm);
    assert_float(q1_normalized.v.y, 4 / norm);
    assert_float(q1_normalized.v.z, 5 / norm);

    return Status::Ok;
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

auto QuatToMatIdentity() -> Status {
    ARC::mat3 m_ref;

    const ARC::quat q;
    ARC::mat3 m = q.Mat();
    const ARC::quat q2(1, 0, 0, 0);
    ARC::mat3 m2 = q2.Mat();
    // Compare identity matrix with identity quaternion
    for(auto i = 0u; i < m.data.size(); ++i) {
        assert_float(m.data[i], m_ref.data[i]);
        assert_float(m2.data[i], m_ref.data[i]);
    }
    return Status::Ok;
}

auto QuatToMat2() -> Status {
    // TODO more complex rotation comparisons
    ARC::mat3 m_ref;

    const ARC::quat q;
    ARC::mat3 m = q.Mat();
    // Compare identity matrix with identity quaternion
    for(auto i = 0u; i < m.data.size(); ++i) {
        assert_float(m.data[i], m_ref.data[i]);
    }
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
    case Tests::QuatToMatIdentity:
        ret = QuatToMatIdentity(); break;
    case Tests::QuatToMat2:
        ret = QuatToMat2(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
