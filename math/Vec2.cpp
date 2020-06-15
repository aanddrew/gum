#include "Vec2.h"

namespace gum {

Vec2::Vec2(float x, float y) {
    this-> x = x;
    this-> y = y;
}

Vec2::Vec2(const Vec2& vec) {
    this->x = vec.x;
    this->y = vec.y;
}

Vec2::Vec2()
: Vec2(0, 0)
{}


void Vec2::operator +=(const Vec2& other) {
    x += other.x;
    y += other.y;
}

void Vec2::operator -=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
}

void Vec2::operator *=(float scalar) {
    x *= scalar;
    y *= scalar;
}

void Vec2::operator /=(float scalar) {
    x /= scalar;
    y /= scalar;
}

Vec2& Vec2::operator =(const Vec2& other) {
    x = other.x;
    y = other.y;
    return *this;
}

Vec2 Vec2::operator +(const Vec2& other) const {
    return Vec2(
        x + other.x,
        y + other.y
    );
}

Vec2 Vec2::operator -(const Vec2& other) const {
    return Vec2(
        x - other.x,
        y - other.y
    );
}

Vec2 Vec2::operator *(float scalar) const {
    return Vec2(
        x * scalar,
        y * scalar
    );
}

Vec2 Vec2::operator /(float scalar) const {
    return Vec2(
        x / scalar,
        y / scalar
    );
}

float Vec2::operator[](int index) const {
    switch(index) {
        case 0: return x; break;
        case 1: return y; break;
    }
    throw std::invalid_argument("Vector index out of bounds");
}

float Vec2::magnitude() const {
    return sqrt(magnitude_squared());
}

float Vec2::magnitude_squared() const {
    return dot(*this, *this);
}

Vec2 Vec2::normalize() const {
    float mag = magnitude();
    if(mag == 0)
        return *this;
    return *this / mag;
}

float Vec2::dot(const Vec2& first, const Vec2& second) {
    return first.x * second.x 
         + first.y * second.y;
}

}
