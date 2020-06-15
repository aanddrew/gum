#pragma once

#include "Mat4.h"
#include "Vec3.h"
#include "Vec4.h"

namespace gum {

class Mat4; //forward declaration because we use Quat in Mat4
    
class Quat {
public:
    Quat();
    Quat(float re, Vec3 im);
    Quat(float a, float b, float c, float d);

    Quat operator*(const Quat& other);

    static Quat rotate(const Vec3& axis, float angle);

    static Mat4 to_mat4(const Quat& q);

    friend std::ostream& operator<<(std::ostream& os, const Quat& quat){
        os << quat.re << " + " << quat.im.x << "i + " << quat.im.y << "j + " << quat.im.z << "k";
        return os;
    }

    float re;
    Vec3  im;

private:
    Vec4 to_vec4() const;
};

}
