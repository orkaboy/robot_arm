#pragma once

#include "vec.hpp"

namespace ARC {

class mat3;

class quat {
public:
    quat();
    quat(Real s_, Real vx, Real vy, Real vz);
    quat(Real s_, const vec3& v_);
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

    mat3 Mat() const;

    Real s;
    vec3 v;
};

} // namespace ARC
