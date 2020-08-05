#pragma once

#include "../math/Math.h"
#include "Object3D.h"
#include "Camera.h"

#include <GL/glew.h>

#include <vector>

namespace gum {

/*
 * Represents a mesh, i.e. an object with vertices and normal vectors coming out
 * of them. Submits vertex data to the vertex shader with layout 0 being positions,
 * and layout 1 being normals
 *
 * render_helper also submits 5 uniforms to the shader program
 *
 * mat4 "model" being this objects own transform
 * mat4 "view" being the view matrix from the camera
 * mat4 "modelview" being view * model
 * mat4 "mvp" being the camera's projection matrix - projection * view * model
 * vec3 "cameraPos" being the location of the camera
 */

class Mesh : public Object3D {
public:
    //load a mesh from a .obj file containing one object
    Mesh(const std::string& objfile);

    //gives a cube mesh
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
