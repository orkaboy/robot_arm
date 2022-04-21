#pragma once

#include "vec.hpp"
#include <array>

namespace ARC {

/* Cubic Bezier curve (4 control points) */
class curve {
public:
    using ControlPoints = std::array<vec3, 4>;

    curve();
    curve(vec3 p0, vec3 p1, vec3 p2, vec3 p3);
    curve(const curve& c);
    curve& operator=(const curve& c);

    /* Sample a point along the curve. 0 <= t <= 1 */
    vec3 sample(Real t) const;

    ControlPoints p;
};

} // namespace ARC

template <> struct fmt::v8::formatter<ARC::curve> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const ARC::curve& c, FormatContext& ctx) -> decltype(ctx.out()) {
        return format_to(ctx.out(), "[{} {} {} {}]", c.p[0], c.p[1], c.p[2], c.p[3]);
    }
};
