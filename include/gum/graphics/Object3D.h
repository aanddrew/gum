#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "../math/Math.h"

#include <GL/glew.h>

#include <vector>
#include <memory>

namespace gum {
class Camera;

/*
 * This is the fundamental class of this engine.
 *
 * Everything that exists inside the 3d world extends this class.
 *
 * The fundamental property of any Object3D is its transform - a Mat4 which 
 * details its orientation, location, and scaling in space.
 *
 * In order to get an Object3D's transform relative to the world, the transform
 * from each parent up until this object is multiplied together. This 
 * effectively attaches objects to other ones in a tree-like structure called
 * a scene graph.
 */

class Object3D {
public:
    Object3D();
    Object3D(Vec3 pos);
    
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
