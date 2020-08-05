#pragma once

#include "../math/Math.h"
#include "../graphics/Object3D.h"

#include <GL/glew.h>

namespace gum {

/*
 * AABB or Axis-Aligned Bounding Box
 *
 * This class is a box which has a corner at its transforms origin, and 
 * a public data member for its dimensions.
 *
 * The opposite corner of the box is found at its origin + dimensions.
 *
 * It contains useful utilities to check if a point is inside the box, or if
 * it is intersecting with another box.
 */

class AABB : public Object3D {
public:
    AABB();
    AABB(Vec3 dimensions);
    bool isTouching(AABB& other);
    bool push(AABB& other);
    bool contains(const Vec3& point);

    Vec3 dimensions;

    void render_helper(GLuint shaderProgram, Camera& camera, const Mat4& proj_view);

    static void draw_wireframes(bool drawn);
};

}
