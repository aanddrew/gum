#include "../../include/math/Mat4.h"
#include <math.h>

#include <iostream>

namespace gum {

Mat4::Mat4() {
    *this = identity();
}

Mat4::Mat4(const Mat3& mat) {
    this->cols[0] = Vec4(mat.cols[0], 0);
    this->cols[1] = Vec4(mat.cols[1], 0);
    this->cols[2] = Vec4(mat.cols[2], 0);
    this->cols[3] = Vec4(0,0,0,1);
}

Mat4::Mat4(const Vec4& first, const Vec4& second, const Vec4& third, const Vec4& fourth) {
    this->cols[0] = first;
    this->cols[1] = second;
    this->cols[2] = third;
    this->cols[3] = fourth;
}

Vec4& Mat4::operator[](int index) {
    if (index < 0 || index > 3)
        throw std::invalid_argument("Matrix index out of bounds");
    return cols[index];
}

Vec4& Mat4::col(int index) {
    return (*this)[index];
}

Vec4 Mat4::row(int index) const {
    if (index < 0 || index > 3)
        throw std::invalid_argument("Matrix index out of bounds");
    return Vec4(
        this->cols[0][index], 
        this->cols[1][index], 
        this->cols[2][index],
        this->cols[3][index]
    );
}

Vec4 Mat4::operator*(const Vec4& other) const {
    return Vec4(
        Vec4::dot(row(0),other),
        Vec4::dot(row(1),other),
        Vec4::dot(row(2),other),
        Vec4::dot(row(3),other)
    );
}

Vec3 Mat4::operator*(const Vec3& other) const {
    Vec4 other4 = Vec4(other, 1);
    Vec4 transformed = {
        Vec4::dot(row(0), other4),
        Vec4::dot(row(1), other4),
        Vec4::dot(row(2), other4),
        Vec4::dot(row(3), other4)
    };
    transformed /= transformed.w;
    return Vec3(transformed.x, transformed.y, transformed.z);
}

Mat4 Mat4::operator*(const Mat4& other) const {
    return Mat4(
        (*this)*other.cols[0],
        (*this)*other.cols[1],
        (*this)*other.cols[2],
        (*this)*other.cols[3]
    );
}


float* Mat4::data() {
    return cols[0].data();
}

Mat3 Mat4::basis() const {
    return Mat3(
        Vec3(cols[0][0], cols[0][1], cols[0][2]),
        Vec3(cols[1][0], cols[1][1], cols[1][2]),
        Vec3(cols[2][0], cols[2][1], cols[2][2])
    );
}

Vec3 Mat4::origin() const {
    return Vec3(
        cols[3][0], cols[3][1], cols[3][2]
    );
}


Mat4 Mat4::transpose(const Mat4& mat) {
    return Mat4(
        mat.row(0), mat.row(1), mat.row(2), mat.row(3)
    );
}

Mat4 Mat4::translate(const Vec3& delta) {
    return {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        Vec4(delta),
    };
}

Mat4 Mat4::rotate(const Vec3& axis, float angle) {
    Quat rotation_quat = Quat::rotate(axis, angle);
    return Quat::to_mat4(rotation_quat);
}

Mat4 Mat4::perspective(float near, float far, float aspect, float fov) {
    float top = tan(fov * 0.5 * M_PI/180.0f) * near;
    float bottom = -top;

    float right = top * aspect;
    float left = bottom * aspect;

    //basically copied from wikipedia
    return {
        {2 * near / (right - left), 0, 0, 0},
        {0, 2 * near/ (top - bottom), 0, 0 },
        { 
          (right + left) / (right - left), 
          (top + bottom) / (top - bottom), 
          -(far + near)/(far - near), 
          -1
        },
        {0, 0, -2*far*near/(far - near), 0},
    };
}

Mat4 Mat4::identity() {
    return {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
}

}
