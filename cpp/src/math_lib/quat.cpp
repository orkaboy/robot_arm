#include "quat.hpp"
#include <fmt/core.h>

namespace ARC {

quat::quat()
    : s(0.0)
{}

quat::quat(float s_, const vec3& v_)
    : s(s_), v(v_)
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

} // namespace ARC
