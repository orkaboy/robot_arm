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

    float s;
    vec3 v;
};

} // namespace ARC
