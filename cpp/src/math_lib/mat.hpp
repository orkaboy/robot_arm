#pragma once

#include "vec.hpp"
#include <array>

namespace ARC {

class quat;

// column major mat3
class mat3 {
public:
    mat3();
    mat3(
        Real m0, Real m3, Real m6,
        Real m1, Real m4, Real m7,
        Real m2, Real m5, Real m8
    );
    mat3& operator=(const mat3& m);
    static mat3 Identity();

    std::string str(bool newline = false) const;

    mat3 operator+(const mat3& m) const;
    mat3& operator+=(const mat3& m);
    mat3 operator-(const mat3& m) const;
    mat3& operator-=(const mat3& m);
    mat3 operator*(Real s) const;
    mat3& operator*=(Real s);
    mat3 operator*(const mat3& m) const;
    mat3& operator*=(const mat3& m);
    vec3 operator*(const vec3& v) const;

    mat3 transpose() const;
    mat3 inverse() const;
    Real determinant() const;

    quat Quat() const;

    std::array<Real, 9> data = {0.0};
};

} // namespace ARC
