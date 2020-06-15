#version 330 core

//vec3 sun_dir = vec3(1,1,0);

in vec3 norm;
in vec3 lightdirection;

out vec3 color;
void main() {
    float cosTheta = clamp( -1*dot(norm, lightdirection), 0, 1); 
    if (lightdirection.length() < 0.5) {
        cosTheta = 0.5;
    }
    //color = vec3(1,0,0) * cosTheta;
    color = lightdirection;
    color = vec3(1,0,0);
}
