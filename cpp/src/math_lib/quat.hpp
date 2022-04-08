#pragma once

#include "vec.hpp"
#include <fmt/format.h>

namespace ARC {

class mat3;

class quat {
public:
    quat();
    quat(Real s_, Real vx, Real vy, Real vz);
    quat(Real s_, const vec3& v_);
    quat(const quat& q);
    quat& operator=(const quat& q);

    quat operator+(const quat& q) const;
    quat& operator+=(const quat& q);
    quat operator-(const quat& q) const;
    quat operator-() const;
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

    /* Spherical linear interpolation, SLERP */
    quat slerp(quat p, Real t) const;
    /* Normalized LERP */
    quat nlerp(quat p, Real t) const;

    mat3 Mat() const;

    Real s;
    vec3 v;
};

} // namespace ARC

template <> struct fmt::formatter<ARC::quat> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const ARC::quat& q, FormatContext& ctx) -> decltype(ctx.out()) {
        return format_to(ctx.out(), "[{}, {}]", q.s, q.v);
    }
};
