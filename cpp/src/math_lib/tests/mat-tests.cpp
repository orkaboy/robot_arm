#include "mat.hpp"
#include "quat.hpp"
#include "testbench.hpp"

enum class Tests {
    Mat3Construct = 0,
    Mat3Str = 1,
    Mat3Add = 2,
    Mat3Sub = 3,
    Mat3MulScalar = 4,
    Mat3DivScalar = 5,
    Mat3MulMat = 6,
    Mat3Transpose = 7,
    Mat3Inverse = 8,
    Mat3Determinant = 9,
    Mat3ToQuatIdentity = 10,
    Mat3ToQuat2 = 11,
    Mat3MulVec3 = 12,
};

auto Mat3Construct() -> Status {
    const ARC::mat3 m;
    assert_float(m.data[0], 1);
    assert_float(m.data[1], 0);
    assert_float(m.data[2], 0);
    assert_float(m.data[3], 0);
    assert_float(m.data[4], 1);
    assert_float(m.data[5], 0);
    assert_float(m.data[6], 0);
    assert_float(m.data[7], 0);
    assert_float(m.data[8], 1);
    const ARC::mat3 identity = ARC::mat3::Identity();
    assert_float(identity.data[0], 1);
    assert_float(identity.data[1], 0);
    assert_float(identity.data[2], 0);
    assert_float(identity.data[3], 0);
    assert_float(identity.data[4], 1);
    assert_float(identity.data[5], 0);
    assert_float(identity.data[6], 0);
    assert_float(identity.data[7], 0);
    assert_float(identity.data[8], 1);
    const ARC::mat3 m2(
        0, 3, 6,
        1, 4, 7,
        2, 5, 8
    );
    assert_float(m2.data[0], 0);
    assert_float(m2.data[1], 1);
    assert_float(m2.data[2], 2);
    assert_float(m2.data[3], 3);
    assert_float(m2.data[4], 4);
    assert_float(m2.data[5], 5);
    assert_float(m2.data[6], 6);
    assert_float(m2.data[7], 7);
    assert_float(m2.data[8], 8);
    const ARC::mat3 m3(m2);
    assert_float(m3.data[0], 0);
    assert_float(m3.data[1], 1);
    assert_float(m3.data[2], 2);
    assert_float(m3.data[3], 3);
    assert_float(m3.data[4], 4);
    assert_float(m3.data[5], 5);
    assert_float(m3.data[6], 6);
    assert_float(m3.data[7], 7);
    assert_float(m3.data[8], 8);
    const ARC::mat3 m4 = m2;
    assert_float(m4.data[0], 0);
    assert_float(m4.data[1], 1);
    assert_float(m4.data[2], 2);
    assert_float(m4.data[3], 3);
    assert_float(m4.data[4], 4);
    assert_float(m4.data[5], 5);
    assert_float(m4.data[6], 6);
    assert_float(m4.data[7], 7);
    assert_float(m4.data[8], 8);
    return Status::Ok;
}

auto Mat3Str() -> Status {
    const ARC::mat3 m(
        0, 3, 6,
        1, 4, 7,
        2, 5, 8
    );
    const std::string str1 = fmt::format("{}", m);
    assert(str1 ==
        "[0 3 6, 1 4 7, 2 5 8]"
    );
    const std::string str2 = fmt::format("{:f}", m);
    assert(str2 ==
        "[0 3 6, 1 4 7, 2 5 8]"
    );
    const std::string str3 = fmt::format("{:n}", m);
    assert(str3 ==
        "[0 3 6,\n 1 4 7,\n 2 5 8]"
    );

    return Status::Ok;
}

auto Mat3Add() -> Status {
    const ARC::mat3 m1(
        1, 4, 7,
        2, 5, 8,
        3, 6, 9
    );
    const ARC::mat3 m10(
        10, 40, 70,
        20, 50, 80,
        30, 60, 90
    );
    const ARC::mat3 m100(
        100, 400, 700,
        200, 500, 800,
        300, 600, 900
    );

    ARC::mat3 m3 = m1 + m10;
    assert_float(m3.data[0], 11);
    assert_float(m3.data[1], 22);
    assert_float(m3.data[2], 33);
    assert_float(m3.data[3], 44);
    assert_float(m3.data[4], 55);
    assert_float(m3.data[5], 66);
    assert_float(m3.data[6], 77);
    assert_float(m3.data[7], 88);
    assert_float(m3.data[8], 99);
    m3 = m10 + m1;
    assert_float(m3.data[0], 11);
    assert_float(m3.data[1], 22);
    assert_float(m3.data[2], 33);
    assert_float(m3.data[3], 44);
    assert_float(m3.data[4], 55);
    assert_float(m3.data[5], 66);
    assert_float(m3.data[6], 77);
    assert_float(m3.data[7], 88);
    assert_float(m3.data[8], 99);
    m3 += m100;
    assert_float(m3.data[0], 111);
    assert_float(m3.data[1], 222);
    assert_float(m3.data[2], 333);
    assert_float(m3.data[3], 444);
    assert_float(m3.data[4], 555);
    assert_float(m3.data[5], 666);
    assert_float(m3.data[6], 777);
    assert_float(m3.data[7], 888);
    assert_float(m3.data[8], 999);
    return Status::Ok;
}

auto Mat3Sub() -> Status {
    const ARC::mat3 m111(
        111, 444, 777,
        222, 555, 888,
        333, 666, 999
    );
    const ARC::mat3 m1(
        1, 4, 7,
        2, 5, 8,
        3, 6, 9
    );
    const ARC::mat3 m10(
        10, 40, 70,
        20, 50, 80,
        30, 60, 90
    );

    ARC::mat3 m3 = m111 - m10;
    assert_float(m3.data[0], 101);
    assert_float(m3.data[1], 202);
    assert_float(m3.data[2], 303);
    assert_float(m3.data[3], 404);
    assert_float(m3.data[4], 505);
    assert_float(m3.data[5], 606);
    assert_float(m3.data[6], 707);
    assert_float(m3.data[7], 808);
    assert_float(m3.data[8], 909);
    m3 -= m1;
    assert_float(m3.data[0], 100);
    assert_float(m3.data[1], 200);
    assert_float(m3.data[2], 300);
    assert_float(m3.data[3], 400);
    assert_float(m3.data[4], 500);
    assert_float(m3.data[5], 600);
    assert_float(m3.data[6], 700);
    assert_float(m3.data[7], 800);
    assert_float(m3.data[8], 900);
    return Status::Ok;
}

auto Mat3MulScalar() -> Status {
    const ARC::mat3 m1(
        1, 4, 7,
        2, 5, 8,
        3, 6, 9
    );
    ARC::mat3 m10 = m1 * 10;
    assert_float(m10.data[0], 10);
    assert_float(m10.data[1], 20);
    assert_float(m10.data[2], 30);
    assert_float(m10.data[3], 40);
    assert_float(m10.data[4], 50);
    assert_float(m10.data[5], 60);
    assert_float(m10.data[6], 70);
    assert_float(m10.data[7], 80);
    assert_float(m10.data[8], 90);
    m10 *= 10;
    assert_float(m10.data[0], 100);
    assert_float(m10.data[1], 200);
    assert_float(m10.data[2], 300);
    assert_float(m10.data[3], 400);
    assert_float(m10.data[4], 500);
    assert_float(m10.data[5], 600);
    assert_float(m10.data[6], 700);
    assert_float(m10.data[7], 800);
    assert_float(m10.data[8], 900);
    return Status::Ok;
}

auto Mat3DivScalar() -> Status {
    const ARC::mat3 m100(
        100, 400, 700,
        200, 500, 800,
        300, 600, 900
    );
    ARC::mat3 m10 = m100 / 10;
    assert_float(m10.data[0], 10);
    assert_float(m10.data[1], 20);
    assert_float(m10.data[2], 30);
    assert_float(m10.data[3], 40);
    assert_float(m10.data[4], 50);
    assert_float(m10.data[5], 60);
    assert_float(m10.data[6], 70);
    assert_float(m10.data[7], 80);
    assert_float(m10.data[8], 90);
    m10 /= 10;
    assert_float(m10.data[0], 1);
    assert_float(m10.data[1], 2);
    assert_float(m10.data[2], 3);
    assert_float(m10.data[3], 4);
    assert_float(m10.data[4], 5);
    assert_float(m10.data[5], 6);
    assert_float(m10.data[6], 7);
    assert_float(m10.data[7], 8);
    assert_float(m10.data[8], 9);
    return Status::Ok;
}

auto Mat3MulMat() -> Status {
    const ARC::mat3 m1(
        1, 4, 7,
        2, 5, 8,
        3, 6, 9
    );
    const ARC::mat3 m2(
        3, 2, 1,
        4, 3, 2,
        5, 4, 3
    );

    const ARC::mat3 m3 = m1 * m2;
    assert_float(m3.data[0], 54); // 1*3 + 4*4 + 7*5 = 54
    assert_float(m3.data[1], 66); // 2*3 + 5*4 + 8*5 = 66
    assert_float(m3.data[2], 78); // 3*3 + 6*4 + 9*5 = 78
    assert_float(m3.data[3], 42); // 1*2 + 4*3 + 7*4 = 42
    assert_float(m3.data[4], 51); // 2*2 + 5*3 + 8*4 = 51
    assert_float(m3.data[5], 60); // 3*2 + 6*3 + 9*4 = 60
    assert_float(m3.data[6], 30); // 1*1 + 4*2 + 7*3 = 30
    assert_float(m3.data[7], 36); // 2*1 + 5*2 + 8*3 = 36
    assert_float(m3.data[8], 42); // 3*1 + 6*2 + 9*3 = 42
    return Status::Ok;
}

auto Mat3MulVec3() -> Status {
    const ARC::mat3 identity;
    const ARC::mat3 rot1(
        0, 1, 0,
        0, 0, 1,
        1, 0, 0
    );
    const ARC::vec3 v1(1, 2, 3);
    const ARC::vec3 v2 = identity * v1;
    assert_float(v2.x, 1);
    assert_float(v2.y, 2);
    assert_float(v2.z, 3);
    // Note: column major
    const ARC::vec3 v3 = rot1 * v1;
    assert_float(v3.x, 2);
    assert_float(v3.y, 3);
    assert_float(v3.z, 1);
    return Status::Ok;
}

auto Mat3Transpose() -> Status {
    const ARC::mat3 m1(
        1, 4, 7,
        2, 5, 8,
        3, 6, 9
    );
    const ARC::mat3 t1 = m1.transpose();
    assert_float(t1.data[0], 1);
    assert_float(t1.data[1], 4);
    assert_float(t1.data[2], 7);
    assert_float(t1.data[3], 2);
    assert_float(t1.data[4], 5);
    assert_float(t1.data[5], 8);
    assert_float(t1.data[6], 3);
    assert_float(t1.data[7], 6);
    assert_float(t1.data[8], 9);
    return Status::Ok;
}

auto Mat3Inverse() -> Status {
    return Status::Err;
}

auto Mat3Determinant() -> Status {
    const ARC::mat3 m1(
        1, 4, 7,
        2, 5, 8,
        3, 6, 9
    );
    const ARC::Real det = m1.determinant();
    // Det = 1*5*9 + 4*8*3 + 7*2*6 - 7*5*3 - 4*2*9 - 1*8*6
    // Det = 45 + 96 + 84 - 105 - 72 - 48 = 0
    assert_float(det, 0);
    return Status::Ok;
}

auto Mat3ToQuatIdentity() -> Status {
    const ARC::mat3 identity;
    const ARC::quat q_identity = identity.Quat();
    assert_float(q_identity.s, 1);
    assert_float(q_identity.v.x, 0);
    assert_float(q_identity.v.y, 0);
    assert_float(q_identity.v.z, 0);
    return Status::Ok;
}

auto Mat3ToQuat2() -> Status {
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
    case Tests::Mat3Construct:
        ret = Mat3Construct(); break;
    case Tests::Mat3Str:
        ret = Mat3Str(); break;
    case Tests::Mat3Add:
        ret = Mat3Add(); break;
    case Tests::Mat3Sub:
        ret = Mat3Sub(); break;
    case Tests::Mat3MulScalar:
        ret = Mat3MulScalar(); break;
    case Tests::Mat3DivScalar:
        ret = Mat3DivScalar(); break;
    case Tests::Mat3MulMat:
        ret = Mat3MulMat(); break;
    case Tests::Mat3Transpose:
        ret = Mat3Transpose(); break;
    case Tests::Mat3Inverse:
        ret = Mat3Inverse(); break;
    case Tests::Mat3Determinant:
        ret = Mat3Determinant(); break;
    case Tests::Mat3ToQuatIdentity:
        ret = Mat3ToQuatIdentity(); break;
    case Tests::Mat3ToQuat2:
        ret = Mat3ToQuat2(); break;
    case Tests::Mat3MulVec3:
        ret = Mat3MulVec3(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
