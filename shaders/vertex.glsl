#version 330 core

layout(location = 0) in vec3 location;
layout(location = 1) in vec3 normal;

uniform mat4 mvp = mat4(1.0);

out vec3 norm;
out vec3 lightdirection;

void main() {
    vec4 trans = mvp * vec4(location, 1.0);

    norm = normal;
    if (normal.length() <0.5) {
        gl_Position = vec4(0);
    }
    else {
        gl_Position = trans;
    }
    lightdirection = normalize(vec3(-1,-1,-1));
}
