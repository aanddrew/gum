#include "../../include/math/Vec4.h"

namespace gum {

Vec4::Vec4(float x, float y, float z, float w) {
    this-> x = x;
    this-> y = y;
    this-> z = z;
    this-> w = w;
}

Vec4::Vec4(const Vec4& vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
    this->w = vec.w;
}

Vec4::Vec4(const Vec3& other, float w) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = w;
}

Vec4::Vec4(const Vec3& other)
: Vec4(other, 1)
{}

Vec4::Vec4()
: Vec4(0, 0, 0, 0)
{}

Vec4& Vec4::operator =(const Vec4& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

Vec4& Vec4::operator =(const Vec3& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = 1;
    return *this;
}

void Vec4::operator +=(const Vec4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
}

void Vec4::operator -=(const Vec4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
}

void Vec4::operator *=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
}

void Vec4::operator /=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
}

Vec4 Vec4::operator +(const Vec4& other) const {
    return Vec4(
        x + other.x,
        y + other.y,
        z + other.z,
        w + other.w
    );
}

Vec4 Vec4::operator -(const Vec4& other) const {
    return Vec4(
        x - other.x,
        y - other.y, 
        z - other.z,
        w - other.w
    );
}

Vec4 Vec4::operator *(float scalar) const {
    return Vec4(
        x * scalar,
        y * scalar,
        z * scalar,
        w * scalar
    );
}

Vec4 Vec4::operator /(float scalar) const {
    return Vec4(
        x / scalar,
        y / scalar,
        z / scalar,
        w / scalar
    );
}

float Vec4::operator[](int index) const {
    switch(index) {
        case 0: return x; break;
        case 1: return y; break;
        case 2: return z; break;
        case 3: return w; break;
    }
    throw std::invalid_argument("Vector index out of bounds");
}

float* Vec4::data() {
    return &x;
}

float Vec4::magnitude() const {
    return sqrt(magnitude_squared());
}

float Vec4::magnitude_squared() const {
    return dot(*this, *this);
}

Vec4 Vec4::normalize() const {
    float mag = magnitude();
    if(mag == 0)
        return *this;
    return *this / mag;
}

float Vec4::dot(const Vec4& first, const Vec4& second) {
    return first.x * second.x 
         + first.y * second.y 
         + first.z * second.z
         + first.w * second.w;
}

}
