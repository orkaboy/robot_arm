#pragma once

#include <string>
#include <fmt/format.h>

namespace ARC {

using Real = double;

Real clamp(Real value, Real min, Real max);
Real deg2rad(Real angleInDegs);
Real rad2deg(Real angleInRads);

class quat;

class vec3 {
public:
    vec3();
    vec3(Real x_, Real y_, Real z_);
    vec3(const vec3& v);
    vec3& operator=(const vec3& v);

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
    vec3 projOntoPlane(const vec3& normal) const; // Project this vector onto the plane described by the normal

    Real norm() const;
    vec3 normalize() const;
    Real angle(const vec3& v) const;
    Real angleSigned(const vec3& v, const vec3& normalVector) const;

    static quat toRotation(const vec3& a, const vec3& b); // Orientation between a->b

    // rotate
    vec3 rotate(Real angle, const vec3& axis) const;
    vec3 rotate(const quat& q) const;

    Real x{};
    Real y{};
    Real z{};
};

} // namespace ARC

namespace fmt {
namespace v8 {

    template <> struct formatter<ARC::vec3> {
        constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
            return ctx.end();
        }

        template <typename FormatContext>
        auto format(const ARC::vec3& v, FormatContext& ctx) -> decltype(ctx.out()) {
            return format_to(ctx.out(), "({} {} {})", v.x, v.y, v.z);
        }
    };

}
}
