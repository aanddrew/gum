#version 330 core

layout(location = 0) in vec3 location;
layout(location = 1) in vec3 normal;

uniform mat4 mvp = mat4(1.0);

out vec3 normalOut;
out vec3 lightOut;

void main() {
    vec4 trans = mvp * vec4(location, 1.0);
    gl_Position = trans;

    normalOut = mat3(mvp) * normal;
    lightOut = normalize(vec3(0,0,-1));
}
