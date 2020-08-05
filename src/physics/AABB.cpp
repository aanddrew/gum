#include "../../include/gum/physics/AABB.h"

#include <algorithm>

#include <iostream>

#include "../../include/gum/graphics/Shader.h"

namespace gum {

static const GLfloat cube_vertices[] = {
    0.0f,0.0f,0.0f, 
    0.0f,0.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 
    1.0f, 1.0f,0.0f, 
    0.0f,0.0f,0.0f,
    0.0f, 1.0f,0.0f,
    1.0f,0.0f, 1.0f,
    0.0f,0.0f,0.0f,
    1.0f,0.0f,0.0f,
    1.0f, 1.0f,0.0f,
    1.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f,0.0f,
    1.0f,0.0f, 1.0f,
    0.0f,0.0f, 1.0f,
    0.0f,0.0f,0.0f,
    0.0f, 1.0f, 1.0f,
    0.0f,0.0f, 1.0f,
    1.0f,0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,0.0f,0.0f,
    1.0f, 1.0f,0.0f,
    1.0f,0.0f,0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,0.0f,
    0.0f, 1.0f,0.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f,0.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f,0.0f, 1.0f
};

std::string wire_vertCode =
"#version 330 core\n"
"layout(location = 0) in vec3 location;\n"
"uniform mat4 mvp;\n"
"uniform vec3 color;\n"
"out vec3 colorOut;\n"
"void main() {\n"
    "vec4 trans = mvp * vec4(location, 1.0);\n"
    "gl_Position = trans;\n"
    "colorOut = color;\n"
"}\n"
;

std::string wire_fragCode =
"#version 330 core\n"
"in vec3 colorOut;\n"
"out vec3 color;\n"
"void main() {\n"
    "color = colorOut;\n"
"}\n"
;

static bool wireframes_should_be_drawn = false;
static bool AABB_initialized = false;
static GLuint wireShader;
static GLuint vertexArray;
static GLuint vertexBuffer;
static Vec3 wireColor;

AABB::AABB() 
: AABB(Vec3(1.0f, 1.0f, 1.0f))
{}

AABB::AABB(Vec3 dimensions){
    this->dimensions = dimensions;
    if (!AABB_initialized) {
        //load wireshader program
        std::cout << "Initializing AABBs" << std::endl;
        wireShader = LoadShadersByCode(wire_vertCode, wire_fragCode);

        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableVertexAttribArray(0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        wireColor = Vec3(1.0f, 0.0f, 0.0f);

        AABB_initialized = true;
    }
}


bool greaterthan(const Vec3& a, const Vec3& b) {
    return a.x >= b.x && a.y >= b.y && a.z >= b.z;
}

bool lessthan(const Vec3& a, const Vec3& b) {
    return a.x <= b.x && a.y <= b.y && a.z <= b.z;
}


Vec3 maxVec(const Vec3& a, const Vec3& b) {
    return Vec3(
            std::max(a.x, b.x),
            std::max(a.y, b.y),
            std::max(a.z, b.z)
    );  
}

Vec3 minVec(const Vec3& a, const Vec3& b) {
    return Vec3(
            std::min(a.x, b.x),
            std::min(a.y, b.y),
            std::min(a.z, b.z)
    );   
}

bool AABB::contains(const Vec3& point) {
    Mat4 this_transform = this->world_transform();

    Vec3 this_corner1 = this_transform.origin();
    Vec3 this_corner2 = this_corner1 + (this->get_root()->local_transform().basis() * this->dimensions);

    Vec3 this_mincorner = minVec(this_corner1, this_corner2);
    Vec3 this_maxcorner = maxVec(this_corner1, this_corner2);

    return greaterthan(point, this_mincorner) && lessthan(point, this_maxcorner);
}

bool AABB::isTouching(AABB& other) {
    Object3D* root = this->get_root();
    if (other.get_root() != root) {
        throw std::runtime_error("Two AABBs don't have the same root!!!");
    }

    Mat4 this_transform = this->world_transform();
    Mat4 other_transform = other.world_transform();

    Vec3 this_corner1 = this_transform.origin();
    Vec3 this_corner2 = this_corner1 + (root->local_transform().basis() * this->dimensions);

    Vec3 other_corner1 = other_transform.origin();
    Vec3 other_corner2 = other_corner1 + (root->local_transform().basis() * this->dimensions);

    Vec3 this_mincorner = minVec(this_corner1, this_corner2);
    Vec3 this_maxcorner = maxVec(this_corner1, this_corner2);
    Vec3 other_mincorner = minVec(other_corner1, other_corner2);
    Vec3 other_maxcorner = maxVec(other_corner1, other_corner2);

    return 
        (this_mincorner.x <= other_maxcorner.x && this_maxcorner.x >= other_mincorner.x) //x axis
        && (this_mincorner.y <= other_maxcorner.y && this_maxcorner.y >= other_mincorner.y) //y axis
        && (this_mincorner.z <= other_maxcorner.z && this_maxcorner.z >= other_mincorner.z) //z axis
        ;

}

void AABB::render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view) {
    if (wireframes_should_be_drawn) {
        Mat4 model = Mat4::translate(this->world_transform().origin());

        model = model * this->get_root()->local_transform() * 
            Mat4(Mat3(
                gum::Vec3(dimensions[0], 0, 0),
                gum::Vec3(0, dimensions[1], 0),
                gum::Vec3(0, 0, dimensions[2])
            ));
        Mat4 mvp = proj_view * model;

        glUseProgram(wireShader);

        glUniformMatrix4fv(glGetUniformLocation(wireShader, "mvp"), 1, GL_FALSE, mvp.data());
        glUniform3fv(glGetUniformLocation(wireShader, "color"), 1, wireColor.data());

        glBindVertexArray(vertexArray);
        glDrawArrays(GL_LINES, 0, sizeof(cube_vertices) / sizeof(float));
    } 

    //important to call the parent function 
    Object3D::render_helper(shaderProgram, camera, proj_view);
}

void AABB::draw_wireframes(bool drawn) {
    wireframes_should_be_drawn = drawn;
}

bool AABB::push(AABB& other) {
    Object3D* root = this->get_root();
    if (other.get_root() != root) {
        throw std::runtime_error("Two AABBs don't have the same root!!!");
    }

    Mat4 this_transform = this->world_transform();
    Mat4 other_transform = other.world_transform();

    Vec3 this_corner1 = this_transform.origin();
    Vec3 this_corner2 = this_corner1 + (root->local_transform().basis() * this->dimensions);

    Vec3 other_corner1 = other_transform.origin();
    Vec3 other_corner2 = other_corner1 + (root->local_transform().basis() * this->dimensions);

    Vec3 this_mincorner = minVec(this_corner1, this_corner2);
    Vec3 this_maxcorner = maxVec(this_corner1, this_corner2);
    Vec3 other_mincorner = minVec(other_corner1, other_corner2);
    Vec3 other_maxcorner = maxVec(other_corner1, other_corner2);

    enum {
        MIN_DX,
        MAX_DX,
        MIN_DY,
        MAX_DY,
        MIN_DZ,
        MAX_DZ,
        NUM_DELTAS,
    };
    float deltas[NUM_DELTAS];

    deltas[MIN_DX] = this_mincorner.x - other_maxcorner.x;
    deltas[MAX_DX] = this_maxcorner.x - other_mincorner.x;
    deltas[MIN_DY] = this_mincorner.y - other_maxcorner.y;
    deltas[MAX_DY] = this_maxcorner.y - other_mincorner.y;
    deltas[MIN_DZ] = this_mincorner.z - other_maxcorner.z;
    deltas[MAX_DZ] = this_maxcorner.z - other_mincorner.z;

    if ((this_mincorner.x <= other_maxcorner.x && this_maxcorner.x >= other_mincorner.x) //x axis
        && (this_mincorner.y <= other_maxcorner.y && this_maxcorner.y >= other_mincorner.y) //y axis
        && (this_mincorner.z <= other_maxcorner.z && this_maxcorner.z >= other_mincorner.z) //z axis
       ) {
            
        int smallest_index = 0;
        float smallest_delta = abs(deltas[0]);
        for (int i = 1; i < NUM_DELTAS; i++) {
            if (abs(deltas[i]) < smallest_delta) {
                smallest_delta = abs(deltas[i]);
                smallest_index = i;
            }
        }
        switch (smallest_index) {
            case MIN_DX:
                other.set_transform(gum::Mat4::translate(gum::Vec3(deltas[MIN_DX], 0, 0)) * other.local_transform());
            break;
            case MAX_DX:
                other.set_transform(gum::Mat4::translate(gum::Vec3(deltas[MAX_DX], 0, 0)) * other.local_transform());
            break;
            case MIN_DY:
                other.set_transform(gum::Mat4::translate(gum::Vec3(0, deltas[MIN_DY], 0)) * other.local_transform());
            break;
            case MAX_DY:
                other.set_transform(gum::Mat4::translate(gum::Vec3(0, deltas[MAX_DY], 0)) * other.local_transform());
            break;
            case MIN_DZ:
                other.set_transform(gum::Mat4::translate(gum::Vec3(0, 0, deltas[MIN_DZ])) * other.local_transform());
            break;
            case MAX_DZ:
                other.set_transform(gum::Mat4::translate(gum::Vec3(0, 0, deltas[MAX_DZ])) * other.local_transform());
            break;
        }
        return true;
    }
    return false;
}

}
