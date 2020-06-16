#version 330 core

//vec3 sun_dir = vec3(1,1,0);

in vec3 normalOut;
in vec3 lightOut;

out vec3 color;
void main() {
    float cosTheta = clamp( dot(normalOut, lightOut), 0.1, 1); 
    color = vec3(1,1,1) * cosTheta;
    //color = normalOut;
    /*
    color = vec3(
        clamp(normalOut.x, 0, 1),
        clamp(normalOut.y, 0, 1),
        clamp(normalOut.z, 0, 1)
    );
    */
}
