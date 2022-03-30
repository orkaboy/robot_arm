#include "mat.hpp"
#include "quat.hpp"
#include "testbench.hpp"

enum class Tests {
    Mat3Construct = 0,
    Mat3Str = 1,
    Mat3Add = 2,
    Mat3Mul = 3,
    Mat3Transpose = 4,
    Mat3Inverse = 5,
    Mat3Determinant = 6,
    Mat3ToQuat = 7,
};

auto Mat3Construct() -> Status {
    ARC::mat3 m;
    assert_float(m.data[0], 1);
    assert_float(m.data[1], 0);
    assert_float(m.data[2], 0);
    assert_float(m.data[3], 0);
    assert_float(m.data[4], 1);
    assert_float(m.data[5], 0);
    assert_float(m.data[6], 0);
    assert_float(m.data[7], 0);
    assert_float(m.data[8], 1);
    ARC::mat3 identity = ARC::mat3::Identity();
    assert_float(identity.data[0], 1);
    assert_float(identity.data[1], 0);
    assert_float(identity.data[2], 0);
    assert_float(identity.data[3], 0);
    assert_float(identity.data[4], 1);
    assert_float(identity.data[5], 0);
    assert_float(identity.data[6], 0);
    assert_float(identity.data[7], 0);
    assert_float(identity.data[8], 1);
    ARC::mat3 m2(
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
    ARC::mat3 m3(m2);
    assert_float(m3.data[0], 0);
    assert_float(m3.data[1], 1);
    assert_float(m3.data[2], 2);
    assert_float(m3.data[3], 3);
    assert_float(m3.data[4], 4);
    assert_float(m3.data[5], 5);
    assert_float(m3.data[6], 6);
    assert_float(m3.data[7], 7);
    assert_float(m3.data[8], 8);
    ARC::mat3 m4 = m2;
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
    return Status::Err;
}

auto Mat3Add() -> Status {
    return Status::Err;
}

auto Mat3Mul() -> Status {
    return Status::Err;
}

auto Mat3Transpose() -> Status {
    return Status::Err;
}

auto Mat3Inverse() -> Status {
    return Status::Err;
}

auto Mat3Determinant() -> Status {
    return Status::Err;
}

auto Mat3ToQuat() -> Status {
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
    case Tests::Mat3Mul:
        ret = Mat3Mul(); break;
    case Tests::Mat3Transpose:
        ret = Mat3Transpose(); break;
    case Tests::Mat3Inverse:
        ret = Mat3Inverse(); break;
    case Tests::Mat3Determinant:
        ret = Mat3Determinant(); break;
    case Tests::Mat3ToQuat:
        ret = Mat3ToQuat(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
