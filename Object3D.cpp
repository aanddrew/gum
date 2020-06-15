#include "Object3D.h"

#include <iostream>

#include "Camera.h"

namespace gum {

Object3D::Object3D() {
}

Mat4 Object3D::get_transform() {
    if ( this->parent == nullptr ) {
        return this->transform * this->parent->get_transform();
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
    std::cout << dt << std::endl;
}

void Object3D::kill() {
}

void Object3D::render_helper(GLuint shaderProgram, const Mat4& proj_view) {
    (void)(shaderProgram);
    (void)(proj_view);
}

void Object3D::render(GLuint shaderProgram) {
    Object3D* camera_obj = find_child("Camera");
    if (camera_obj == nullptr) {
        throw std::runtime_error("Cannot render tree without camera!");
    }

    Camera* camera = (Camera*) camera_obj;

    Mat4 proj_view = camera->getProjection() * camera->getView();
    for ( auto child : children ) {
        child->render_helper(shaderProgram, proj_view);
    }
}

}
