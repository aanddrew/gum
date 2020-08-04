#include "../include/gum/Light.h"

#include <iostream>

static int num_lights = 0;
static const int max_lights = 10;

namespace gum {

Light::Light(Vec3 pos) 
: Object3D(pos) {
    index = num_lights;
    num_lights++;
    if (num_lights == max_lights + 1) {
        throw std::runtime_error("Too many lights!");
    }
    std::cout << "num_lights: " << num_lights << std::endl;
    this->set_transform(gum::Mat4::translate(pos));
}

Light::Light() : Light(Vec3(0,0,0)) { }

void Light::render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view) {
    (void)(shaderProgram);
    (void)(camera);
    (void)(proj_view);
    static Vec3 light_positions[max_lights];

    Vec3 location = this->world_transform().origin();
    light_positions[this->index] = location;

    if (this->index != num_lights -1) {
        return;
    }
    glUniform3fv(glGetUniformLocation(shaderProgram, "lights"), num_lights, (float*) light_positions);
    glUniform1iv(glGetUniformLocation(shaderProgram, "num_lights"), 1, &num_lights);
}

}
