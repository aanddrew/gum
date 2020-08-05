#pragma once

#include "Object3D.h"

namespace gum {

/*
 * Represents a Camera.
 *
 * Has easy utilities for computing the model and view matrices given its own transform.
 *
 * It uses the basis and origin of its own transform, as well as a private projection
 * matrix to compute this.
 *
 * The projection type is flexible and can simply be changed by modifying the projection
 * data member from inside the class.
 */

class Camera : public Object3D {
public:
    Camera(float aspect);

    enum PROJECTION_TYPE {
        PERSPECTIVE,
        ORTHOGRAPHIC,
    };

    Mat4 getView() const;
    Mat4 getProjection() const;

    PROJECTION_TYPE getType();
private:
    PROJECTION_TYPE type;
    Mat4 projection;
};

}
