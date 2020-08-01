#version 330 core

layout(location = 0) in vec3 location;
layout(location = 1) in vec3 normal;

uniform mat4 mvp = mat4(1.0);
uniform mat4 model = mat4(1.0);
uniform mat4 modelview = mat4(1.0);
uniform vec3 cameraPos;

out vec3 normalOut;
out vec3 lightPos;
out vec3 fragPos;
out vec3 cameraPosOut;

void main() {
    vec4 trans = mvp * vec4(location, 1.0);
    gl_Position = trans;

    vec4 worldLoc = modelview * vec4(location, 1.0);
    fragPos = vec3(worldLoc / worldLoc.w);

    normalOut = mat3(model) * normal;
    lightPos = vec3(5,0,10);
}
