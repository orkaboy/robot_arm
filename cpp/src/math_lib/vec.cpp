#include "vec.hpp"
#include <cmath>

namespace ARC {


vec3::vec3()
    : x(0.0), y(0.0), z(0.0)
{}

vec3::vec3(Real x_, Real y_, Real z_)
    : x(x_), y(y_), z(z_)
{}

vec3::vec3(const vec3& v)
    : x(v.x), y(v.y), z(v.z)
{}

vec3& vec3::operator=(const vec3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

vec3& vec3::operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3 vec3::operator+(const vec3& v) const {
    return vec3(x+v.x, y+v.y, z+v.z);
}

vec3& vec3::operator-=(const vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vec3 vec3::operator-(const vec3& v) const {
    return vec3(x-v.x, y-v.y, z-v.z);
}

vec3 vec3::operator-() const {
    return vec3(-x, -y, -z);
}


vec3& vec3::operator*=(Real s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

vec3 vec3::operator*(Real s) const {
    return vec3(x*s, y*s, z*s);
}

vec3& vec3::operator/=(Real s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

vec3 vec3::operator/(Real s) const {
    return vec3(x/s, y/s, z/s);
}

Real vec3::operator*(const vec3& v) const {
    return x*v.x + y*v.y + z*v.z;
}

Real vec3::dot(const vec3& v) const {
    return x*v.x + y*v.y + z*v.z;
}

vec3 vec3::cross(const vec3& v) const {
    return vec3(
        y*v.z - z*v.y,
        z*v.x - x*v.z,
        x*v.y - y*v.x
    );
}

Real vec3::len() const {
    return std::sqrt(x*x + y*y + z*z);
}

vec3 vec3::norm() const {
    auto magnitude = len();
    if(magnitude > 0.0f) {
        auto oneOverMag = 1.0f / magnitude;
        return vec3(x*oneOverMag, y*oneOverMag, z*oneOverMag);
    }
    return *this;
}

Real vec3::angle(const vec3& v) const {
    auto dotProd = dot(v);
    auto lenProd = len() * v.len();
    if(lenProd > 0.0f) {
        auto cosTheta = dotProd / lenProd;
        return std::acos(cosTheta);
    }
    return 0.0;
}

} // namespace ARC
