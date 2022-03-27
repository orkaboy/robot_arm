#pragma once

#include <string>

namespace ARC {

using Real = float;

class vec3 {
public:
    vec3();
    vec3(Real x_, Real y_, Real z_);
    vec3(const vec3& v);
    vec3& operator=(const vec3& v);

    std::string str() const;

    static vec3 X() { return vec3(1, 0, 0); }
    static vec3 Y() { return vec3(0, 1, 0); }
    static vec3 Z() { return vec3(0, 0, 1); }

    vec3& operator+=(const vec3& v);
    vec3 operator+(const vec3& v) const;
    vec3& operator-=(const vec3& v);
    vec3 operator-(const vec3& v) const;
    vec3 operator-() const;
    vec3& operator*=(Real s);
    vec3 operator*(Real s) const;
    vec3& operator/=(Real s);
    vec3 operator/(Real s) const;

    Real operator*(const vec3& v) const; // dot product
    Real dot(const vec3& v) const;
    vec3 cross(const vec3& v) const;
    vec3 proj(const vec3& v) const; // Project this vector onto v

    Real norm() const;
    vec3 normalize() const;
    Real angle(const vec3& v) const;

    // rotate
    vec3 rotate(Real angle, const vec3& axis) const;

    Real x{};
    Real y{};
    Real z{};
};

} // namespace ARC
