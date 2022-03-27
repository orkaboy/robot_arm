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
