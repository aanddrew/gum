#version 330 core

layout(location = 0) in vec3 location;
layout(location = 1) in vec3 normal;

uniform mat4 mvp = mat4(1.0);
uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 modelview = mat4(1.0);
uniform vec3 cameraPos;

uniform vec3 lights[10];
uniform int num_lights;

out vec3 normalOut;
flat out int num_lights_out;
flat out vec3 lightsOut[10];
out vec3 fragPos;
out vec3 cameraPosOut;

void main() {
    vec4 trans = mvp * vec4(location, 1.0);
    gl_Position = trans;


    vec4 worldLoc = model * vec4(location, 1.0);
    fragPos = vec3(worldLoc / worldLoc.w);

    normalOut = mat3(model) * normal;
    lightsOut = lights;
    num_lights_out = num_lights;
    cameraPosOut = vec3(0,0,0);
}
