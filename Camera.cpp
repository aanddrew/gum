#include "Camera.h"

namespace gum {

Camera::Camera(float aspect) {
    projection = Mat4::perspective(0.01f, 200.0f, aspect, 90.0f);
}

Mat4 Camera::getView() const {
    //transform basis should be orthogonal, so we can simply transpose it
    //that's some epic math right there
    gum::Mat3 rot_inv = gum::Mat3::transpose(local_transform().basis());
    gum::Mat4 translate_inverse = gum::Mat4::translate(world_transform().origin() * -1);

    return Mat4(rot_inv) * translate_inverse;
}

Mat4 Camera::getProjection() const {
    return projection;
}

}
