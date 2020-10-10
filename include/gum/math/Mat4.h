#pragma once

#include "Mat3.h"
#include "Vec3.h"
#include "Vec4.h"

#include "Quat.h"

namespace gum {

class Mat4{
public:
    Mat4();
    Mat4(const Mat3& mat);
    Mat4(const Vec4& first, const Vec4& second, const Vec4& third, const Vec4& fourth);

    Vec4& operator[](int index);
    Vec4 row(int index) const;
    Vec4& col(int index);
    Vec4 operator*(const Vec4& other) const;
    Vec3 operator*(const Vec3& other) const;
    Mat4 operator*(const Mat4& other) const;

    float* data();

    Mat3 basis() const;
    Vec3 origin() const;

    static Mat4 transpose(const Mat4& mat);
    static Mat4 translate(const Vec3& delta);
    static Mat4 rotate(const Vec3& axis, float angle);
    static Mat4 identity();

    static Mat4 perspective(float near, float far, float ar, float fov);
    static Mat4 ortho(float bottom, float top, float left, float right, float near, float far);

    friend std::ostream& operator<<(std::ostream& os, const Mat4& mat){
        os << "|" << mat.row(0) << "|" << std::endl 
           << "|" << mat.row(1) << "|" << std::endl 
           << "|" << mat.row(2) << "|" << std::endl
           << "|" << mat.row(3) << "|";
        return os;
    }

    Vec4 cols[4];
};

}
