#include "vec.hpp"
#include <cmath>

#include <fmt/core.h>

#include "quat.hpp"

namespace ARC {

Real clamp(Real value, Real min, Real max) {
    return std::min(std::max(value, min), max);
}

Real deg2rad(Real angleInDegs) {
    return (angleInDegs / 180.0) * M_PI;
}

Real rad2deg(Real angleInRads) {
    return (angleInRads / M_PI) * 180.0;
}


std::string vec3::str() const {
    return fmt::format("({} {} {})", x, y, z);
}

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

vec3 vec3::proj(const vec3& v) const {
    return v * (dot(v) / v.dot(v)); // a' = b * ((a . b) / (b . b))
}

// Project this vector onto the plane described by the normal
vec3 vec3::projOntoPlane(const vec3& normal) const {
    if(normal.norm() <= 0.0) {
        return *this;
    }
    // Projection of vector b onto plane with normal n is defined as: b - ( b.n / ( |n| squared )) * n
    vec3 b = normalize();
    vec3 n = normal.normalize();
    return (b - n * b.dot(normal)).normalize(); 
}

Real vec3::norm() const {
    return std::sqrt(x*x + y*y + z*z);
}

vec3 vec3::normalize() const {
    auto magnitude = norm();
    if(magnitude > 0.0) {
        auto oneOverMag = 1.0f / magnitude;
        return vec3(x*oneOverMag, y*oneOverMag, z*oneOverMag);
    }
    return *this;
}

Real vec3::angle(const vec3& v) const {
    auto dotProd = dot(v);
    auto lenProd = norm() * v.norm();
    if(lenProd > 0.0) {
        auto cosTheta = dotProd / lenProd;
        return std::acos(cosTheta); // TODO is this good? Or should atan2 be used?
    }
    return 0.0;
}

/*
*this vector is the baseline, zero degrees vector
v is the vector to calculate the angle to the baseline
normalVector is a vector perpendicular to both the baseline and v
The return value is the angle in radians between the vectors, between -M_PI and M_PI 
*/
Real vec3::angleSigned(const vec3& v, const vec3& normalVector) const {
    auto unsignedAngle = angle(v);
    auto sign = cross(v).dot(normalVector) >= 0.0 ? 1.0 : -1.0;
    return unsignedAngle * sign;
}

vec3 vec3::rotate(Real angle, const vec3& axis_) const {
    auto pure = quat(0, (*this));
    auto axis = axis_.normalize();
    auto q = quat(angle, axis).unitnorm();
    auto qInv = q.inverse();
    auto rotVec = q * pure * qInv;
    return rotVec.v;
}

} // namespace ARC
