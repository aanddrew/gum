#pragma once

#include <ostream>
#include <math.h>

namespace gum {

class Vec3 {
public:
    Vec3(float, float, float);
    Vec3(const Vec3& vec);
    Vec3();
    
    Vec3& operator =(const Vec3& other);

    void operator +=(const Vec3& other);
    void operator -=(const Vec3& other);
    void operator *=(float scalar);
    void operator /=(float scalar);

    Vec3  operator +(const Vec3& other) const;
    Vec3  operator -(const Vec3& other) const;
    Vec3  operator *(float scalar) const;
    Vec3  operator /(float scalar) const;
    
    float operator[](int index) const;

    float* data();

    float magnitude() const;
    float magnitude_squared() const;
    Vec3  normalize() const;

    static float  dot(const Vec3& first, const Vec3& second);
    static Vec3 cross(const Vec3& first, const Vec3& second);

    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec){
        os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
        return os;
    }

    float x, y, z;
};

}
