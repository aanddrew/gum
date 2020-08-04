#include "../../include/gum/math/Quat.h"

#include <iostream>

#include <math.h>

namespace gum {
    
Quat::Quat() {
    re = 1.0f;
}

Quat::Quat(float re, Vec3 im) {
    this->im = im;
    this->re = re;
}

Quat::Quat(float a, float b, float c, float d) {
    this->re = a;
    this->im = Vec3(b,c,d);
}

Quat Quat::operator*(const Quat& other) {
    return Quat(
            this->re * other.re - Vec3::dot(this->im, other.im), 
            Vec3::cross(this->im, other.im) + (other.im * this->re) + (this->im * other.re)
    );
}

//please give a unit axis
Quat Quat::rotate(const Vec3& axis, float angle) {
    //returns q from wikipedia formula
    float sin_half = sin(angle / 2);
    float cos_half = cos(angle / 2);

    return Quat(cos_half, axis * sin_half);
}

Mat4 Quat::to_mat4(const Quat& q) {
    return Mat4(
        {
            1 - 2*(q.im.y*q.im.y + q.im.z*q.im.z),
            2*(q.im.x*q.im.y + q.re*q.im.z),
            2*(q.im.x*q.im.z - q.re*q.im.y),
            0
        },
        {
            2*(q.im.x*q.im.y - q.re*q.im.z),
            1 - 2*(q.im.x*q.im.x + q.im.z*q.im.z),
            2*(q.re*q.im.x + q.im.y*q.im.z),
            0
        },
        {
            2*(q.re*q.im.y + q.im.x*q.im.z),
            2*(q.im.y*q.im.z - q.re*q.im.x),
            1 - 2*(q.im.x*q.im.x + q.im.y*q.im.y),
            0
        },
        {
            0, 0, 0, 1
        }
    );
}

Vec4 Quat::to_vec4() const {
    return Vec4(this->re, this->im.x, this->im.y, this->im.z);
}

}

