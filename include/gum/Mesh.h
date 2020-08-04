#pragma once

#include "math/Math.h"
#include "Object3D.h"
#include "Camera.h"

#include <GL/glew.h>

#include <vector>

namespace gum {

class Mesh : public Object3D {
public:
    Mesh(const std::string& objfile);

    static Mesh Cube();
    
    float* vertexData();
    float* normalData();

    virtual void render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view);

private:
    std::vector<gum::Vec3> vertices;
    std::vector<gum::Vec3> normals;

    GLuint vertexArray;

    GLuint vertexBuffer;
    GLuint normalBuffer;
};

};
