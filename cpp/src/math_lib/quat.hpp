#pragma once

#include "vec.hpp"

namespace ARC {

class quat {
public:
    quat();
    quat(float s_, const vec3& v_);
    quat(const quat& q);
    quat& operator=(const quat& q);

    std::string str() const;

    quat operator+(const quat& q) const;
    quat& operator+=(const quat& q);
    quat operator-(const quat& q) const;
    quat& operator-=(const quat& q);
    quat operator*(const quat& q) const;
    quat& operator*=(const quat& q);
    quat operator*(Real r) const;
    quat& operator*=(Real r);

    Real norm() const;
    Real norm2() const;
    quat normalize() const;
    quat unitnorm() const;

    quat conjugate() const;
    quat inverse() const;

    float s;
    vec3 v;
};

} // namespace ARC
