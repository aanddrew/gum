#include "../../include/gum/math/IVec2.h"

namespace gum {

IVec2::IVec2(int x, int y) {
    this-> x = x;
    this-> y = y;
}

IVec2::IVec2(const IVec2& vec) {
    this->x = vec.x;
    this->y = vec.y;
}

IVec2::IVec2()
: IVec2(0, 0)
{}


void IVec2::operator +=(const IVec2& other) {
    x += other.x;
    y += other.y;
}

void IVec2::operator -=(const IVec2& other) {
    x -= other.x;
    y -= other.y;
}

void IVec2::operator *=(int scalar) {
    x *= scalar;
    y *= scalar;
}

void IVec2::operator /=(int scalar) {
    x /= scalar;
    y /= scalar;
}

IVec2& IVec2::operator =(const IVec2& other) {
    x = other.x;
    y = other.y;
    return *this;
}

IVec2 IVec2::operator +(const IVec2& other) const {
    return IVec2(
        x + other.x,
        y + other.y
    );
}

IVec2 IVec2::operator -(const IVec2& other) const {
    return IVec2(
        x - other.x,
        y - other.y
    );
}

IVec2 IVec2::operator *(int scalar) const {
    return IVec2(
        x * scalar,
        y * scalar
    );
}

IVec2 IVec2::operator /(int scalar) const {
    return IVec2(
        x / scalar,
        y / scalar
    );
}

int IVec2::operator[](int index) const {
    switch(index) {
        case 0: return x; break;
        case 1: return y; break;
    }
    throw std::invalid_argument("Vector index out of bounds");
}

}
