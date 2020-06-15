#pragma once

#include <ostream>
#include <math.h>

namespace gum {

class Vec2 {
public:
    Vec2(float, float);
    Vec2(const Vec2& vec);
    Vec2();
    
    Vec2& operator =(const Vec2& other);

    void operator +=(const Vec2& other);
    void operator -=(const Vec2& other);
    void operator *=(float scalar);
    void operator /=(float scalar);

    Vec2  operator +(const Vec2& other) const;
    Vec2  operator -(const Vec2& other) const;
    Vec2  operator *(float scalar) const;
    Vec2  operator /(float scalar) const;

    float operator[](int index) const;

    float magnitude() const;
    float magnitude_squared() const;
    Vec2  normalize() const;

    static float dot(const Vec2& first, const Vec2& second);

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec){
        os << "<" << vec.x << ", " << vec.y << ">";
        return os;
    }

    float x, y;
};

}
