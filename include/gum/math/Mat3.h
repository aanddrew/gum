#pragma once

#include "Vec3.h"

namespace gum {

class Mat3{
public:
    Mat3(const Vec3& first, const Vec3& second, const Vec3& third);

    const Vec3& operator[](int index) const;
    Vec3 row(int index) const;
    Vec3 operator*(const Vec3& other);

    static Mat3 identity();
    static Mat3 transpose(const Mat3& mat);

    friend std::ostream& operator<<(std::ostream& os, const Mat3& mat){
        os << "|" << mat.row(0) << "|" << std::endl 
           << "|" << mat.row(1) << "|" << std::endl 
           << "|" << mat.row(2) << "|";
        return os;
    }

    Vec3 cols[3];
};

}
