#pragma once

namespace ARC {

using Real = float;

class vec3 {
public:
    vec3();
    vec3(Real x_, Real y_, Real z_);
    vec3(const vec3& v);
    vec3& operator=(const vec3& v);

    vec3& operator+=(const vec3& v);
    vec3 operator+(const vec3& v) const;
    vec3& operator-=(const vec3& v);
    vec3 operator-(const vec3& v) const;
    vec3 operator-() const;
    vec3& operator*=(Real s);
    vec3 operator*(Real s) const;
    vec3& operator/=(Real s);
    vec3 operator/(Real s) const;

    // dot product
    Real operator*(const vec3& v) const;
    Real dot(const vec3& v) const;
    vec3 cross(const vec3& v) const;

    Real len() const;
    vec3 norm() const;
    Real angle(const vec3& v) const;

    Real x{};
    Real y{};
    Real z{};
};

} // namespace ARC
