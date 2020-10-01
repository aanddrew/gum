#include "../../include/gum/graphics/Object3D.h"

#include <iostream>

#include "../../include/gum/graphics/Camera.h"

namespace gum {

Object3D::Object3D() 
: Object3D(Vec3(0,0,0))
{}

Object3D::Object3D(Vec3 pos) {
    this->parent = nullptr;
    this->shader_program = 0;
    this->transform = Mat4::identity().translate(pos);
}

Mat4 Object3D::local_transform() const {
    return this->transform;
}

Mat4 Object3D::world_transform() const {
    if ( this->parent != nullptr ) {
        return this->parent->world_transform() * this->transform;
    }
    return this->transform;
}

void Object3D::set_transform(Mat4 transform) {
    this->transform = transform;
}

Object3D* get_root_helper(Object3D* object) {
    if (object->get_parent() != nullptr) {
        return get_root_helper(object->get_parent());
    }
    return object;
}

Object3D* Object3D::get_root() {
    return get_root_helper(this);
}

Object3D* Object3D::get_parent() {
    return parent;
}

void Object3D::add_child(Object3D* object) {
    object->parent = this;
    this->children.push_back(object);
}

Object3D* Object3D::find_child(const std::string& name) {
    if (this->name == name) {
        return this;
    }
    else {
        for( auto child : this->children ) {
            auto ret = child->find_child(name);
            if (ret != nullptr)
                return ret;
        }
    }
    return nullptr;
}


void Object3D::init() {
}

void Object3D::update(float dt) {
    for ( auto child : children ) {
        child->update(dt);
    }
}

void Object3D::kill() {
}

//called on all children nodes
void Object3D::render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view) {
    for ( auto child : children ) {
        if (child->shader_program != 0) {
            shaderProgram = child->shader_program;
        }
        child->render_helper(shaderProgram, camera, proj_view);
    }
}

//called on root node
void Object3D::render() {
    Object3D* camera_obj = find_child("Camera");
    if (camera_obj == nullptr) {
        throw std::runtime_error("Cannot render tree without camera!");
    }
    if (shader_program == 0) {
        throw std::runtime_error("Root node must have a shader program attached!");
    }

    int sun_exists = 0;
    Object3D* sun = find_child("Sun");
    if (sun) {
        sun_exists = 1;
        Vec3 sun_position = sun->world_transform().origin();
        glUniform3fv(glGetUniformLocation(shader_program, "sunPosition"), 1, (float*) &sun_position);
    }
    glUniform1iv(glGetUniformLocation(shader_program, "sunExists"), 1, &sun_exists);

    Camera* camera = (Camera*) camera_obj;

    Mat4 proj_view = camera->getProjection() * camera->getView();
    for ( auto child : children ) {
        child->render_helper(shader_program, *camera, proj_view);
    }
}

size_t Object3D::get_num_children() { return children.size(); }
Object3D* Object3D::get_child(size_t index) { return children.at(index); }

void print_helper(Object3D* object, int level) {
    for(int i = 0; i < level; i++) {
        std::cout << "    ";
    }
    std::cout << object->name << std::endl;
    for( size_t i = 0; i < object->get_num_children(); i++ ) {
        print_helper(object->get_child(i), level + 1);
    }
}

void Object3D::print() {
    print_helper(this, 0);
}

}
