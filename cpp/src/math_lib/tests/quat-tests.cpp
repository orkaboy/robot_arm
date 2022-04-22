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
    QuatFromAxisAngle = 14,
};

auto QuatConstruct() -> Status {
    const ARC::quat q1;
    assert_float(q1.s, 0.0);
    assert_float(q1.v.x, 0.0);
    assert_float(q1.v.y, 0.0);
    assert_float(q1.v.z, 0.0);
    const ARC::quat q2(1,2,3,4);
    assert_float(q2.s, 1);
    assert_float(q2.v.x, 2);
    assert_float(q2.v.y, 3);
    assert_float(q2.v.z, 4);
    const ARC::quat q3(1, {2,3,4});
    assert_float(q3.s, 1);
    assert_float(q3.v.x, 2);
    assert_float(q3.v.y, 3);
    assert_float(q3.v.z, 4);
    const ARC::quat q4(q3);
    assert_float(q4.s, 1);
    assert_float(q4.v.x, 2);
    assert_float(q4.v.y, 3);
    assert_float(q4.v.z, 4);
    const ARC::quat q5 = q3;
    assert_float(q5.s, 1);
    assert_float(q5.v.x, 2);
    assert_float(q5.v.y, 3);
    assert_float(q5.v.z, 4);
    return Status::Ok;
}

auto QuatStr() -> Status {
    const ARC::quat q1;
    const std::string q1str = fmt::format("{}", q1);
    assert(q1str == "[0, (0 0 0)]");
    const ARC::quat q2(1, 2, 3, 4);
    const std::string q2str = fmt::format("{}", q2);
    assert(q2str == "[1, (2 3 4)]");
    return Status::Ok;
}

auto QuatAdd() -> Status {
    const ARC::quat q1(1, 2, 3, 4);
    const ARC::quat q2(5, 6, 7, 8);
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
    const ARC::quat q1(5, 6, 7, 8);
    const ARC::quat q2(4, 3, 2, 1);
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
    const ARC::quat _q1 = -q1;
    assert_float(_q1.s, -5);
    assert_float(_q1.v.x, -6);
    assert_float(_q1.v.y, -7);
    assert_float(_q1.v.z, -8);

    return Status::Ok;
}

auto QuatMul() -> Status {
    // Quaternion math says that:
    // i^2 = j^2 = k^2 = -1
    // ij = -ji = k
    // jk = -kj = i
    // ki = -ik = j
    const ARC::quat minus1(-1, 0, 0, 0);
    const ARC::quat i(0, 1, 0, 0);
    const ARC::quat j(0, 0, 1, 0);
    const ARC::quat k(0, 0, 0, 1);
    // ij = -ji = k
    const ARC::quat ij = i * j;
    assert_float(ij.s, k.s);
    assert_float(ij.v.x, k.v.x);
    assert_float(ij.v.y, k.v.y);
    assert_float(ij.v.z, k.v.z);
    const ARC::quat _ji = -j * i;
    assert_float(_ji.s, k.s);
    assert_float(_ji.v.x, k.v.x);
    assert_float(_ji.v.y, k.v.y);
    assert_float(_ji.v.z, k.v.z);
    // jk = -kj = i
    const ARC::quat jk = j * k;
    assert_float(jk.s, i.s);
    assert_float(jk.v.x, i.v.x);
    assert_float(jk.v.y, i.v.y);
    assert_float(jk.v.z, i.v.z);
    const ARC::quat _kj = -k * j;
    assert_float(_kj.s, i.s);
    assert_float(_kj.v.x, i.v.x);
    assert_float(_kj.v.y, i.v.y);
    assert_float(_kj.v.z, i.v.z);
    // ki = -ik = j
    const ARC::quat ki = k * i;
    assert_float(ki.s, j.s);
    assert_float(ki.v.x, j.v.x);
    assert_float(ki.v.y, j.v.y);
    assert_float(ki.v.z, j.v.z);
    const ARC::quat _ik = -i * k;
    assert_float(_ik.s, j.s);
    assert_float(_ik.v.x, j.v.x);
    assert_float(_ik.v.y, j.v.y);
    assert_float(_ik.v.z, j.v.z);
    // i^2 = j^2 = k^2 = -1
    const ARC::quat ii = i*i;
    assert_float(ii.s, minus1.s);
    assert_float(ii.v.x, minus1.v.x);
    assert_float(ii.v.y, minus1.v.y);
    assert_float(ii.v.z, minus1.v.z);
    const ARC::quat jj = j*j;
    assert_float(jj.s, minus1.s);
    assert_float(jj.v.x, minus1.v.x);
    assert_float(jj.v.y, minus1.v.y);
    assert_float(jj.v.z, minus1.v.z);
    const ARC::quat kk = k*k;
    assert_float(kk.s, minus1.s);
    assert_float(kk.v.x, minus1.v.x);
    assert_float(kk.v.y, minus1.v.y);
    assert_float(kk.v.z, minus1.v.z);
    return Status::Ok;
}

auto QuatScalarMul() -> Status {
    const ARC::quat q1(1, 2, 3, 4);
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
    const ARC::quat q1(2, 3, 4, 5);
    // sqrt(4 + 9 + 16 + 25) = sqrt(54)
    const ARC::Real norm = q1.norm();
    assert_float(norm, std::sqrt(54));
    // 4 + 9 + 16 + 25 = 54
    const ARC::Real norm2 = q1.norm2();
    assert_float(norm2, 54);
    return Status::Ok;
}

auto QuatNormalize() -> Status {
    const ARC::quat q0;
    const ARC::quat q0_normalized = q0.normalize();
    assert_float(q0_normalized.s, 0);
    assert_float(q0_normalized.v.x, 0);
    assert_float(q0_normalized.v.y, 0);
    assert_float(q0_normalized.v.z, 0);

    const ARC::quat q1(2, 3, 4, 5);
    const ARC::Real norm = q1.norm();
    const ARC::quat q1_normalized = q1.normalize();
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
    const ARC::mat3 m_ref;

    const ARC::quat q;
    const ARC::mat3 m = q.Mat();
    const ARC::quat q2(1, 0, 0, 0);
    const ARC::mat3 m2 = q2.Mat();
    // Compare identity matrix with identity quaternion
    for(auto i = 0u; i < m.data.size(); ++i) {
        assert_float(m.data[i], m_ref.data[i]);
        assert_float(m2.data[i], m_ref.data[i]);
    }
    return Status::Ok;
}

auto QuatToMat2() -> Status {
    // TODO more complex rotation comparisons
    const ARC::mat3 m_ref;

    const ARC::quat q;
    const ARC::mat3 m = q.Mat();
    // Compare identity matrix with identity quaternion
    for(auto i = 0u; i < m.data.size(); ++i) {
        assert_float(m.data[i], m_ref.data[i]);
    }
    return Status::Err;
}

auto QuatFromAxisAngle() -> Status {
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
    case Tests::QuatFromAxisAngle:
        ret = QuatFromAxisAngle(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
