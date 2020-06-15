#include "Mat3.h"
#include <math.h>

namespace gum {

Mat3::Mat3(const Vec3& first, const Vec3& second, const Vec3& third) {
    this->cols[0] = first;
    this->cols[1] = second;
    this->cols[2] = third;
}

const Vec3& Mat3::operator[](int index) const {
    if (index < 0 || index > 2)
        throw std::invalid_argument("Matrix index out of bounds");
    return cols[index];
}

Vec3 Mat3::row(int index) const {
    if (index < 0 || index > 2)
        throw std::invalid_argument("Matrix index out of bounds");
    return Vec3(
        this->cols[0][index], 
        this->cols[1][index], 
        this->cols[2][index]
    );
}

Vec3 Mat3::operator*(const Vec3& other) {
    return Vec3(
        Vec3::dot(row(0),other),
        Vec3::dot(row(1),other),
        Vec3::dot(row(2),other)
    );
}

Mat3 Mat3::transpose(const Mat3& mat) {
    return Mat3(
        mat.row(0),
        mat.row(1),
        mat.row(2)
    );
}

Mat3 Mat3::identity() {
    return {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    };
}


}
