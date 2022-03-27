#include "bezier.hpp"

namespace ARC {

curve::curve() {}
curve::curve(vec3 p0, vec3 p1, vec3 p2, vec3 p3)
    : p({p0, p1, p2, p3})
{}
curve::curve(const ControlPoints& control) : p(control) {}
curve::curve(const curve& c) : p(c.p) {}
curve& curve::operator=(const curve& c) {
    p = c.p;
    return *this;
}

vec3 curve::sample(Real t) const {
    auto t1 = (1 - t);
    auto t2 = t1 * t1; // (t - 1)^2
    auto t3 = t2 * t1; // (t - 1)^3
    auto T2 = t * t;
    auto T3 = T2 * t;

    // B(t)=P0(1-t)^3 + P1 * 3(1-t)^2 * t + P2 * 3(1-t)t^2 + P3 * t^3
    return (p[0]*t3) + (p[1]*3*t*t2) + (p[2]*3*T2*t1) + (p[3]*T3); 
}

} // namespace ARC
