#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "math/Math.h"

#include <GL/glew.h>

#include <vector>
#include <memory>

namespace gum {
class Camera;

class Object3D {
public:
    Object3D();
    
    Mat4 world_transform() const;
    Mat4 local_transform() const;
    void set_transform(Mat4 transform);
    
    Object3D* get_root();
    Object3D* get_parent();
    
    void add_child(Object3D* object);
    Object3D* find_child(const std::string& name);

    size_t get_num_children();
    Object3D* get_child(size_t index);

    void print();

    virtual void init();
    virtual void update(float dt);
    virtual void kill();

    virtual void render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view);

    void render(GLuint shaderProgram);

    std::string name;

protected:
    Mat4 transform;
    
    Object3D* parent;
    std::vector<Object3D*> children;

private:
};

}

#endif
