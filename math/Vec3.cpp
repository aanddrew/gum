#include "Vec3.h"

namespace gum {

Vec3::Vec3(float x, float y, float z) {
    this-> x = x;
    this-> y = y;
    this-> z = z;
}

Vec3::Vec3(const Vec3& vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
}

Vec3::Vec3()
: Vec3(0, 0, 0)
{}

Vec3& Vec3::operator =(const Vec3& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

void Vec3::operator +=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
}

void Vec3::operator -=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

void Vec3::operator *=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void Vec3::operator /=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
}

Vec3 Vec3::operator +(const Vec3& other) const {
    return Vec3(
        x + other.x,
        y + other.y,
        z + other.z
    );
}

Vec3 Vec3::operator -(const Vec3& other) const {
    return Vec3(
        x - other.x,
        y - other.y, 
        z - other.z
    );
}

Vec3 Vec3::operator *(float scalar) const {
    return Vec3(
        x * scalar,
        y * scalar,
        z * scalar
    );
}

Vec3 Vec3::operator /(float scalar) const {
    return Vec3(
        x / scalar,
        y / scalar,
        z / scalar
    );
}

float Vec3::operator[](int index) const {
    switch(index) {
        case 0: return x; break;
        case 1: return y; break;
        case 2: return z; break;
    }
    throw std::invalid_argument("Vector index out of bounds");
}

float Vec3::magnitude() const {
    return sqrt(magnitude_squared());
}

float Vec3::magnitude_squared() const {
    return dot(*this, *this);
}

Vec3 Vec3::normalize() const {
    float mag = magnitude();
    if(mag == 0)
        return *this;
    return *this / mag;
}

float Vec3::dot(const Vec3& first, const Vec3& second) {
    return first.x * second.x 
         + first.y * second.y 
         + first.z * second.z;
}

Vec3 Vec3::cross(const Vec3& first, const Vec3& second) {
    return Vec3(
        first.y * second.z - first.z * second.y,
        first.z * second.x - first.x * second.z,
        first.x * second.y - first.y * second.x
    );
}

}
