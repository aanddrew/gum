#pragma once

#include "Object3D.h"

namespace gum {

/* 
 * Represents a point light.
 *
 * When render_helper is called on this object, it submits the position data
 * and the number of lights to the shader program through the uniforms:
 * lights and num_lights 
 *
 * It is up to the shader program to decide what to do with this information 
 * */

class Light : public Object3D {
public:
    Light();
    Light(Vec3 pos);
    virtual void render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view);
private:
    int index;
};

}
