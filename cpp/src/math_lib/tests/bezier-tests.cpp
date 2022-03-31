#include "bezier.hpp"
#include "testbench.hpp"

enum class Tests {
    BezierConstruct = 0,
    BezierSampleLine = 1,
    BezierSampleCurve = 2,
};

auto BezierConstruct() -> Status {
    ARC::curve b1;
    assert_float(b1.p[0].x, 0);
    assert_float(b1.p[0].y, 0);
    assert_float(b1.p[0].z, 0);
    assert_float(b1.p[1].x, 0);
    assert_float(b1.p[1].y, 0);
    assert_float(b1.p[1].z, 0);
    assert_float(b1.p[2].x, 0);
    assert_float(b1.p[2].y, 0);
    assert_float(b1.p[2].z, 0);
    assert_float(b1.p[3].x, 0);
    assert_float(b1.p[3].y, 0);
    assert_float(b1.p[3].z, 0);
    ARC::vec3 p1(1,2,3), p2(4,5,6), p3(7,8,9), p4(10,11,12);
    ARC::curve b2(p1, p2, p3, p4);
    assert_float(b2.p[0].x, 1);
    assert_float(b2.p[0].y, 2);
    assert_float(b2.p[0].z, 3);
    assert_float(b2.p[1].x, 4);
    assert_float(b2.p[1].y, 5);
    assert_float(b2.p[1].z, 6);
    assert_float(b2.p[2].x, 7);
    assert_float(b2.p[2].y, 8);
    assert_float(b2.p[2].z, 9);
    assert_float(b2.p[3].x, 10);
    assert_float(b2.p[3].y, 11);
    assert_float(b2.p[3].z, 12);
    ARC::curve b3(b2);
    assert_float(b3.p[0].x, 1);
    assert_float(b3.p[0].y, 2);
    assert_float(b3.p[0].z, 3);
    assert_float(b3.p[1].x, 4);
    assert_float(b3.p[1].y, 5);
    assert_float(b3.p[1].z, 6);
    assert_float(b3.p[2].x, 7);
    assert_float(b3.p[2].y, 8);
    assert_float(b3.p[2].z, 9);
    assert_float(b3.p[3].x, 10);
    assert_float(b3.p[3].y, 11);
    assert_float(b3.p[3].z, 12);
    ARC::curve b4 = b2;
    assert_float(b4.p[0].x, 1);
    assert_float(b4.p[0].y, 2);
    assert_float(b4.p[0].z, 3);
    assert_float(b4.p[1].x, 4);
    assert_float(b4.p[1].y, 5);
    assert_float(b4.p[1].z, 6);
    assert_float(b4.p[2].x, 7);
    assert_float(b4.p[2].y, 8);
    assert_float(b4.p[2].z, 9);
    assert_float(b4.p[3].x, 10);
    assert_float(b4.p[3].y, 11);
    assert_float(b4.p[3].z, 12);
    return Status::Ok;
}

auto BezierSampleLine() -> Status {
    ARC::curve b1(
        {0,0,0},
        {1,1,1},
        {2,2,2},
        {3,3,3}
    );
    ARC::vec3 v1 = b1.sample(0.0);
    ARC::vec3 v2 = b1.sample(1.0/3.0);
    ARC::vec3 v3 = b1.sample(2.0/3.0);
    ARC::vec3 v4 = b1.sample(1.0);
    assert_float(v1.x, 0);
    assert_float(v1.y, 0);
    assert_float(v1.z, 0);
    assert_float(v2.x, 1);
    assert_float(v2.y, 1);
    assert_float(v2.z, 1);
    assert_float(v3.x, 2);
    assert_float(v3.y, 2);
    assert_float(v3.z, 2);
    assert_float(v4.x, 3);
    assert_float(v4.y, 3);
    assert_float(v4.z, 3);
    return Status::Ok;
}

auto BezierSampleCurve() -> Status {
    // TODO more complex curves
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
    case Tests::BezierConstruct:
        ret = BezierConstruct(); break;
    case Tests::BezierSampleLine:
        ret = BezierSampleLine(); break;
    case Tests::BezierSampleCurve:
        ret = BezierSampleCurve(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
