#include "quat.hpp"
#include <fmt/core.h>
#include <cmath>

#include "mat.hpp"

namespace ARC {

quat::quat()
    : s(0.0)
{}

quat::quat(Real s_, const vec3& v_)
    : s(s_), v(v_)
{}

quat::quat(Real s_, Real vx, Real vy, Real vz)
    : s(s_), v(vx, vy, vz)
{}

quat::quat(const quat& q)
    : s(q.s), v(q.v)
{}

quat& quat::operator=(const quat& q) {
    s = q.s;
    v = q.v;
    return *this;
}

std::string quat::str() const {
    return fmt::format("[{}, {}]", s, v.str());
}

quat quat::operator+(const quat& q) const {
    return quat(s+q.s, v+q.v);
}

quat& quat::operator+=(const quat& q) {
    s += q.s;
    v += q.v;
    return *this;
}

quat quat::operator-(const quat& q) const {
    return quat(s-q.s, v-q.v);
}

quat& quat::operator-=(const quat& q) {
    s -= q.s;
    v -= q.v;
    return *this;
}

quat multiply(const quat& q1, const quat& q2) {
    Real scalar = q1.s*q2.s - q1.v.dot(q2.v);
    vec3 imaginary = q2.v*q1.s + q1.v*q2.s + q1.v.cross(q2.v);
    return quat(scalar, imaginary);
}

quat quat::operator*(const quat& q) const {
    return multiply(*this, q);
}

quat& quat::operator*=(const quat& q) {
    (*this) = multiply(*this, q);
    return *this;
}

quat quat::operator*(Real r) const {
    return quat(s*r, v*r);
}

quat& quat::operator*=(Real r) {
    s *= r;
    v *= r;
    return *this;
}

Real quat::norm() const {
    return std::sqrt(s*s + v*v);
}

Real quat::norm2() const {
    return s*s + v*v;
}

quat quat::normalize() const {
    auto n = norm();
    if(n != 0.0) {
        return quat(s/n, v/n);
    }
    return quat();
}

quat quat::unitnorm() const {
    auto s_ = std::cos(s * 0.5);
    auto v_ = v.normalize() * std::sin(s * 0.5);
    return quat(s_, v_);
}

quat quat::conjugate() const {
    return quat(s, -v);
}

//q*q^-1 = 1
quat quat::inverse() const {
    auto n = norm2();
    if(n == 0.0) {
        return quat();
    }

    quat conj = conjugate();
    return quat(conj.s / n, conj.v / n);
}

quat quat::slerp(quat p, Real t) const {
    /* https://www.researchgate.net/post/How_do_I_calculate_the_smallest_angle_between_two_quaternions */
    auto prod = (*this) * p.inverse();
    auto phi2 = std::asin(prod.v.norm());
    /* https://www.mecademic.com/en/how-to-use-quaternions-in-industrial-robotics */
    return (*this) * (std::sin((1-t)*phi2) / std::sin(phi2)) + p * (std::sin(t*phi2) / std::sin(phi2));
}

quat quat::nlerp(quat p, Real t) const {
    /* https://www.mecademic.com/en/how-to-use-quaternions-in-industrial-robotics */
    return ((*this) * (1-t) + p*t).normalize();
}

mat3 quat::Mat() const {
    /* https://www.mecademic.com/en/how-to-use-quaternions-in-industrial-robotics */
    return mat3(
        2*s*s + 2*v.x*v.x - 1,
        2*v.x*v.y - 2*s*v.z,
        2*v.x*v.z + 2*s*v.y,

        2*v.x*v.y + 2*s*v.z,
        2*s*s + 2*v.y*v.y - 1,
        2*v.y*v.z - 2*s*v.x,

        2*v.x*v.z - 2*s*v.y,
        2*v.y*v.z - 2*s*v.x,
        2*s*s + 2*v.z*v.z - 1
    );
}

} // namespace ARC
