#pragma once

#include "../math/Math.h"
#include "../graphics/Object3D.h"

#include <GL/glew.h>

namespace gum {

//only uses the origin to determine the corner of the object
//aligned to the axis of the root node of its tree
class AABB : public Object3D {
public:
    AABB();
    AABB(Vec3 dimensions);
    bool isTouching(AABB& other);
    bool contains(const Vec3& point);

    Vec3 dimensions;

    void render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view);

    static void draw_wireframes(bool drawn);
};

}
