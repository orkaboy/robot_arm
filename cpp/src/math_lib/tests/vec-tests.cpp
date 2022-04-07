#include "vec.hpp"
#include "testbench.hpp"

enum class Tests {
    Vec3Construct = 0,
    Clamp = 1,
    Vec3Axis = 2,
    Vec3Str = 3,
    Vec3Add = 4,
    Vec3Sub = 5,
    Vec3Mul = 6,
    Vec3Div = 7,
    Vec3Dot = 8,
    Vec3Cross = 9,
    Vec3Proj = 10,
    Vec3Norm = 11,
    Vec3Normalize = 12,
    Vec3Angle = 13,
    Vec3AngleSigned = 14,
    Vec3Rotate = 15,
    Deg2Rad = 16,
    Rad2Deg = 17,
    Vec3ProjOntoPlane = 18,
};

auto Vec3Construct() -> Status {
    {
        const ARC::vec3 v;
        assert(v.x == 0.0);
        assert(v.y == 0.0);
        assert(v.z == 0.0);
    }
    {
        const ARC::vec3 v(1.0, 2.0, 3.0);
        assert(v.x == 1.0);
        assert(v.y == 2.0);
        assert(v.z == 3.0);

        const ARC::vec3 v2 = v;
        assert(v.x == 1.0);
        assert(v.y == 2.0);
        assert(v.z == 3.0);

        const ARC::vec3 v3(v);
        assert(v.x == 1.0);
        assert(v.y == 2.0);
        assert(v.z == 3.0);
    }

    return Status::Ok;
}

auto Clamp() -> Status {
    assert(ARC::clamp(0.5, 0.0, 1.0) == 0.5);
    assert(ARC::clamp(0.0, 0.0, 1.0) == 0.0);
    assert(ARC::clamp(-0.5, 0.0, 1.0) == 0.0);
    assert(ARC::clamp(1.5, 0.0, 1.0) == 1.0);
    assert(ARC::clamp(5.0, -4.0, 4.0) == 4.0);
    assert(ARC::clamp(-3.5, -4.0, 1.0) == -3.5);
    assert(ARC::clamp(-0.3, -0.1, 1.0) == -0.1);
    return Status::Ok;
}

auto Deg2Rad() -> Status {
    assert_float(ARC::deg2rad(0.0), 0.0);
    assert_float(ARC::deg2rad(30.0), M_PI/6.0);
    assert_float(ARC::deg2rad(90.0), M_PI/2.0);
    assert_float(ARC::deg2rad(180.0), M_PI);
    assert_float(ARC::deg2rad(-90.0), -M_PI/2.0);
    assert_float(ARC::deg2rad(-180.0), -M_PI);
    return Status::Ok;
}

auto Rad2Deg() -> Status {
    assert_float(ARC::rad2deg(0.0), 0.0);
    assert_float(ARC::rad2deg(M_PI/2.0), 90.0);
    assert_float(ARC::rad2deg(M_PI), 180.0);
    assert_float(ARC::rad2deg(M_PI/6.0), 30.0);
    assert_float(ARC::rad2deg(-M_PI/2), -90.0);
    assert_float(ARC::rad2deg(-M_PI), -180.0);
    return Status::Ok;
}

auto Vec3Axis() -> Status {
    const ARC::vec3 x = ARC::vec3::X();
    assert(x.x == 1.0);
    assert(x.y == 0.0);
    assert(x.z == 0.0);
    const ARC::vec3 y = ARC::vec3::Y();
    assert(y.x == 0.0);
    assert(y.y == 1.0);
    assert(y.z == 0.0);
    const ARC::vec3 z = ARC::vec3::Z();
    assert(z.x == 0.0);
    assert(z.y == 0.0);
    assert(z.z == 1.0);
    
    return Status::Ok;
}

auto Vec3Str() -> Status {
    const ARC::vec3 v;
    std::string str = v.str();
    assert(str == "(0 0 0)");
    
    const ARC::vec3 v1(1, 2, 3);
    str = v1.str();
    assert(str == "(1 2 3)");
    return Status::Ok;
}

auto Vec3Add() -> Status {
    const ARC::vec3 v1(1, 2, 3);
    const ARC::vec3 v2(4, 5, 6);
    // operator+
    ARC::vec3 v3 = v1 + v2;
    assert(v3.x == 5);
    assert(v3.y == 7);
    assert(v3.z == 9);
    // operator+=
    v3 += ARC::vec3(1, 2, 3);
    assert(v3.x == 6);
    assert(v3.y == 9);
    assert(v3.z == 12);

    return Status::Ok;
}

auto Vec3Sub() -> Status {
    const ARC::vec3 v1(6, 9, 12);
    const ARC::vec3 v2(4, 5, 6);
    // operator-
    ARC::vec3 v3 = v1 - v2;
    assert(v3.x == 2);
    assert(v3.y == 4);
    assert(v3.z == 6);
    // operator-=
    v3 -= ARC::vec3(1, 2, 3);
    assert(v3.x == 1);
    assert(v3.y == 2);
    assert(v3.z == 3);
    // operator-(binary)
    const ARC::vec3 v4 = -v2;
    assert(v4.x == -4);
    assert(v4.y == -5);
    assert(v4.z == -6);

    return Status::Ok;
}

auto Vec3Mul() -> Status {
    const ARC::vec3 v1(1, 1, 1);
    // operator*(Real)
    const ARC::vec3 v2 = v1 * 5;
    assert(v2.x == 5);
    assert(v2.y == 5);
    assert(v2.z == 5);
    ARC::vec3 v3(2, 4, 6);
    ARC::vec3 v4 = v3 * 3;
    assert(v4.x == 6);
    assert(v4.y == 12);
    assert(v4.z == 18);
    // operator*=(Real)
    v3 *= 2;
    assert(v3.x == 4);
    assert(v3.y == 8);
    assert(v3.z == 12);
    v4 *= 0.5;
    assert(v4.x == 3);
    assert(v4.y == 6);
    assert(v4.z == 9);
    return Status::Ok;
}

auto Vec3Div() -> Status {
    const ARC::vec3 v1(1, 2, 3);
    // operator/(Real)
    ARC::vec3 v2 = v1 / 2;
    assert(v2.x == 0.5);
    assert(v2.y == 1);
    assert(v2.z == 1.5);
    // operator/=(Real)
    v2 /= 2;
    assert(v2.x == 0.25);
    assert(v2.y == 0.5);
    assert(v2.z == 0.75);
    return Status::Ok;
}

auto Vec3Dot() -> Status {
    const ARC::vec3 v1(1, 2, 3);
    const ARC::vec3 v2(4, 5, 6);
    // operator*(dot prod)
    //1*4 + 2*5 + 3*6 = 32
    ARC::Real dot = v1 * v2;
    assert(dot == 32);
    dot = v2 * v1;
    assert(dot == 32);
    dot = v1.dot(v2);
    assert(dot == 32);
    return Status::Ok;
}

auto Vec3Cross() -> Status {
    const ARC::vec3 x = ARC::vec3::X();
    const ARC::vec3 y = ARC::vec3::Y();
    ARC::vec3 z = x.cross(y);
    assert(z.x == 0);
    assert(z.y == 0);
    assert(z.z == 1);
    z = y.cross(x);
    assert(z.x == 0);
    assert(z.y == 0);
    assert(z.z == -1);
    return Status::Ok;
}

auto Vec3Proj() -> Status {
    const ARC::vec3 x = ARC::vec3::X();
    const ARC::vec3 y = ARC::vec3::Y();
    const ARC::vec3 z = ARC::vec3::Z();
    const ARC::vec3 v1(3, 5, 7);
    // Project v1 onto x
    const ARC::vec3 v2 = v1.proj(x);
    assert(v2.x == 3);
    assert(v2.y == 0);
    assert(v2.z == 0);
    const ARC::vec3 v3 = v1.proj(y);
    assert(v3.x == 0);
    assert(v3.y == 5);
    assert(v3.z == 0);
    const ARC::vec3 v4 = v1.proj(z);
    assert(v4.x == 0);
    assert(v4.y == 0);
    assert(v4.z == 7);
    return Status::Ok;
}

auto Vec3ProjOntoPlane() -> Status {
    const ARC::vec3 x = ARC::vec3::X();
    const ARC::vec3 y = ARC::vec3::Y();
    const ARC::vec3 z = ARC::vec3::Z();
    const ARC::vec3 v1(3, 5, 7);
    // Project v1 onto the planes described by normals
    const ARC::vec3 vx = v1.projOntoPlane(x);
    assert_float(vx.x, 0);
    assert_float(vx.y, 0.5812381937);
    assert_float(vx.z, 0.8137334712);
    const ARC::vec3 vy = v1.projOntoPlane(y);
    assert_float(vy.x, 0.3939192986);
    assert_float(vy.y, 0);
    assert_float(vy.z, 0.9191450300);
    const ARC::vec3 vz = v1.projOntoPlane(z);
    assert_float(vz.x, 0.5144957554);
    assert_float(vz.y, 0.8574929257);
    assert_float(vz.z, 0);
    return Status::Ok;
}

auto Vec3Norm() -> Status {
    const ARC::vec3 v1(3, 4, 0);
    const ARC::Real norm = v1.norm();
    assert(norm == 5);
    return Status::Ok;
}

auto Vec3Normalize() -> Status {
    const ARC::vec3 v1(3, 4, 0);
    const ARC::vec3 v2 = v1.normalize();
    assert_float(v2.x, 0.6);
    assert_float(v2.y, 0.8);
    assert_float(v2.z, 0.0);
    const ARC::vec3 v3(2, 1, 3);
    const ARC::vec3 v4 = v3.normalize();
    assert_float(v4.x, 0.5345224838248488);
    assert_float(v4.y, 0.2672612419124244);
    assert_float(v4.z, 0.8017837257372732);
    return Status::Ok;
}

auto Vec3Angle() -> Status {
    const ARC::vec3 x = ARC::vec3::X();
    const ARC::vec3 y = ARC::vec3::Y();
    const ARC::vec3 z = ARC::vec3::Z();
    assert_float(x.angle(y), M_PI/2);
    assert_float(x.angle(-y), M_PI/2);
    assert_float(x.angle(z), M_PI/2);
    assert_float(x.angle(-z), M_PI/2);
    assert_float(y.angle(z), M_PI/2);
    assert_float(y.angle(-z), M_PI/2);
    return Status::Ok;
}

auto Vec3AngleSigned() -> Status {
    const ARC::vec3 x = ARC::vec3::X();
    const ARC::vec3 y = ARC::vec3::Y();
    const ARC::vec3 z = ARC::vec3::Z();
    assert_float(x.angleSigned(y, z), M_PI/2);
    assert_float(x.angleSigned(-y, z), -M_PI/2);
    assert_float(x.angleSigned(z, y), -M_PI/2);
    assert_float(x.angleSigned(-z, y), M_PI/2);
    assert_float(y.angleSigned(z, x), M_PI/2);
    assert_float(y.angleSigned(-z, x), -M_PI/2);
    return Status::Ok;
}

auto Vec3Rotate() -> Status {
    const ARC::vec3 x = ARC::vec3::X();
    const ARC::vec3 y = ARC::vec3::Y();
    const ARC::vec3 x_inv = x.rotate(M_PI, y); // rotate 180 degrees, will point to -X
    assert_float(x_inv.x, -1);
    assert_float(x_inv.y, 0);
    assert_float(x_inv.z, 0);
    const ARC::vec3 x_rot = x.rotate(M_PI/2, y); // rotate 90 degrees, will point to -Z
    assert_float(x_rot.x, 0);
    assert_float(x_rot.y, 0);
    assert_float(x_rot.z, -1);
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
    case Tests::Vec3Construct:
        ret = Vec3Construct(); break;
    case Tests::Clamp:
        ret = Clamp(); break;
    case Tests::Vec3Axis:
        ret = Vec3Axis(); break;
    case Tests::Vec3Str:
        ret = Vec3Str(); break;
    case Tests::Vec3Add:
        ret = Vec3Add(); break;
    case Tests::Vec3Sub:
        ret = Vec3Sub(); break;
    case Tests::Vec3Mul:
        ret = Vec3Mul(); break;
    case Tests::Vec3Div:
        ret = Vec3Div(); break;
    case Tests::Vec3Dot:
        ret = Vec3Dot(); break;
    case Tests::Vec3Cross:
        ret = Vec3Cross(); break;
    case Tests::Vec3Proj:
        ret = Vec3Proj(); break;
    case Tests::Vec3Norm:
        ret = Vec3Norm(); break;
    case Tests::Vec3Normalize:
        ret = Vec3Normalize(); break;
    case Tests::Vec3Angle:
        ret = Vec3Angle(); break;
    case Tests::Vec3AngleSigned:
        ret = Vec3AngleSigned(); break;
    case Tests::Vec3Rotate:
        ret = Vec3Rotate(); break;
    case Tests::Deg2Rad:
        ret = Deg2Rad(); break;
    case Tests::Rad2Deg:
        ret = Rad2Deg(); break;
    case Tests::Vec3ProjOntoPlane:
        ret = Vec3ProjOntoPlane(); break;

    default:
        break;
    }

    return static_cast<int>(ret);
}
