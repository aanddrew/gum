#pragma once

#include "Object3D.h"

namespace gum {

class Camera : public Object3D {
public:
    Camera(float aspect);

    enum PROJECTION_TYPE {
        PERSPECTIVE,
        ORTHOGRAPHIC,
    };

    //setPerspective(

    Mat4 getView();
    Mat4 getProjection();

    PROJECTION_TYPE getType();
private:
    PROJECTION_TYPE type;
    Mat4 projection;
};

}
