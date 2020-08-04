#pragma once

#include "Object3D.h"

namespace gum {

class Light : public Object3D {
public:
    Light();
    Light(Vec3 pos);
    virtual void render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view);
private:
    int index;
};

}
