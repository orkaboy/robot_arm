#pragma once

#include "vec.hpp"
#include <array>
#include <fmt/format.h>

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

    mat3 operator+(const mat3& m) const;
    mat3& operator+=(const mat3& m);
    mat3 operator-(const mat3& m) const;
    mat3& operator-=(const mat3& m);
    mat3 operator*(Real s) const;
    mat3& operator*=(Real s);
    mat3 operator/(Real s) const;
    mat3& operator/=(Real s);
    mat3 operator*(const mat3& m) const;
    mat3& operator*=(const mat3& m);
    vec3 operator*(const vec3& v) const;

    mat3 transpose() const;
    mat3 inverse() const;
    Real determinant() const;

    quat Quat() const;

    std::array<Real, 9> data = {};

    static char presentation;
};

} // namespace ARC

namespace fmt {
namespace v8 {

    template <> struct formatter<ARC::mat3> {
        // Presentation format: '{:n}' - newline. '{:f}' - flat.
        constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
            // Parse the presentation format and store it in the formatter:
            auto it = ctx.begin(), end = ctx.end();
            if (it != end && (*it == 'f' || *it == 'n')) ARC::mat3::presentation = *it++;

            // Check if reached the end of the range:
            if (it != end && *it != '}') throw format_error("invalid format");

            // Return an iterator past the end of the parsed range:
            return it;
        }

        template <typename FormatContext>
        auto format(const ARC::mat3& m, FormatContext& ctx) -> decltype(ctx.out()) {
            return ARC::mat3::presentation == 'f'
                ? format_to(ctx.out(), "[{} {} {}, {} {} {}, {} {} {}]",
                    m.data[0], m.data[3], m.data[6],
                    m.data[1], m.data[4], m.data[7],
                    m.data[2], m.data[5], m.data[8])
                : format_to(ctx.out(), "[{} {} {},\n {} {} {},\n {} {} {}]",
                    m.data[0], m.data[3], m.data[6],
                    m.data[1], m.data[4], m.data[7],
                    m.data[2], m.data[5], m.data[8]);
        }
    };

}
}
