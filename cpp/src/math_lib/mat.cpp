#include "mat.hpp"
#include <fmt/core.h>

#include "quat.hpp"
#include <cmath>

namespace ARC {

std::string mat3::str(bool newline) const {
    if(newline) {
        return fmt::format("[{} {} {},\n {} {} {}\n {} {} {}]",
            data[0], data[3], data[6],
            data[1], data[4], data[7],
            data[2], data[5], data[8]);
    }
    return fmt::format("[{} {} {}, {} {} {}, {} {} {}]",
        data[0], data[3], data[6],
        data[1], data[4], data[7],
        data[2], data[5], data[8]);
}

mat3::mat3() {
    for(auto& m : data) {
        m = 0.0;
    }
    data[0] = data[4] = data[8] = 1.0;
}

mat3 mat3::Identity() {
    return mat3();
}

mat3::mat3(
    Real m0, Real m3, Real m6,
    Real m1, Real m4, Real m7,
    Real m2, Real m5, Real m8
) {
    data[0] = m0;
    data[3] = m3;
    data[6] = m6;
    
    data[1] = m1;
    data[4] = m4;
    data[7] = m7;
    
    data[2] = m2;
    data[5] = m5;
    data[8] = m8;
}

mat3& mat3::operator=(const mat3& m) {
    for(auto i = 0u; i < data.size(); ++i) {
        data[i] = m.data[i];
    }
    return *this;
}

mat3 mat3::operator+(const mat3& m) const {
    mat3 ret;
    for(auto i = 0u; i < data.size(); ++i) {
        ret.data[i] = data[i] + m.data[i];
    }
    return ret;
}

mat3& mat3::operator+=(const mat3& m) {
    for(auto i = 0u; i < data.size(); ++i) {
        data[i] += m.data[i];
    }
    return *this;
}

mat3 mat3::operator*(Real s) const {
    mat3 ret;
    for(auto i = 0u; i < data.size(); ++i) {
        ret.data[i] = data[i] * s;
    }
    return ret;
}

mat3& mat3::operator*=(Real s) {
    for(auto i = 0u; i < data.size(); ++i) {
        data[i] *= s;
    }
    return *this;
}

mat3 mat3::operator*(const mat3& m) const {
    return mat3(
        data[0]*m.data[0] + data[3]*m.data[1] + data[6]*m.data[2],
        data[0]*m.data[3] + data[3]*m.data[4] + data[6]*m.data[5],
        data[0]*m.data[6] + data[3]*m.data[7] + data[6]*m.data[8],
        
        data[1]*m.data[0] + data[4]*m.data[1] + data[7]*m.data[2],
        data[1]*m.data[3] + data[4]*m.data[4] + data[7]*m.data[5],
        data[1]*m.data[6] + data[4]*m.data[7] + data[7]*m.data[8],
        
        data[2]*m.data[0] + data[5]*m.data[1] + data[8]*m.data[2],
        data[2]*m.data[3] + data[5]*m.data[4] + data[8]*m.data[5],
        data[2]*m.data[6] + data[5]*m.data[7] + data[8]*m.data[8]
    );
}

mat3& mat3::operator*=(const mat3& m) {
    auto mult = *this * m;
    *this = mult;
    return *this;
}

Real mat3::determinant() const {
    // Leibniz formula
    /*
        a=0 b=3 c=6
        d=1 e=4 f=7
        g=2 h=5 i=8
    */
    auto aei = data[0] * data[4] * data[8];
    auto bfg = data[3] * data[7] * data[2];
    auto cdh = data[6] * data[1] * data[5];
    auto ceg = data[6] * data[4] * data[2];
    auto bdi = data[3] * data[1] * data[8];
    auto afh = data[0] * data[7] * data[5];
    return aei + bfg + cdh -(ceg + bdi + afh);
}

mat3 mat3::inverse() const {
    auto det = determinant();
    if(det == 0.0) return mat3();
    auto invd = 1.0 / det;
    return mat3(
         (data[4]*data[8] - data[7]*data[5]),
        -(data[3]*data[8] - data[6]*data[5]),
         (data[3]*data[7] - data[6]*data[4]),
        
        -(data[1]*data[8] - data[7]*data[2]),
         (data[0]*data[8] - data[6]*data[2]),
        -(data[0]*data[7] - data[6]*data[1]),
        
         (data[1]*data[5] - data[4]*data[2]),
        -(data[0]*data[5] - data[3]*data[2]),
         (data[0]*data[4] - data[3]*data[1])
    ) * invd;
}

mat3 mat3::transpose() const {
    return mat3(
        data[0], data[1], data[2],
        data[3], data[4], data[5],
        data[6], data[7], data[8]
    );
}

vec3 mat3::operator*(const vec3& v) const {
    return vec3(
        data[0]*v.x + data[3]*v.y + data[6]*v.z,
        data[1]*v.x + data[4]*v.y + data[7]*v.z,
        data[2]*v.x + data[5]*v.y + data[8]*v.z
    );
}

quat mat3::Quat() const {
    auto signX = std::signbit(data[5] - data[7]) ? -1 : 1;
    auto signY = std::signbit(data[6] - data[2]) ? -1 : 1;
    auto signZ = std::signbit(data[1] - data[3]) ? -1 : 1;
    return quat(
        std::sqrt(1 + data[0] + data[4] + data[8]) / 2,
        std::sqrt(1 + data[0] - data[4] - data[8]) * signX / 2,
        std::sqrt(1 - data[0] + data[4] - data[8]) * signY / 2,
        std::sqrt(1 - data[0] - data[4] + data[8]) * signZ / 2
    );
}

} // namespace ARC
