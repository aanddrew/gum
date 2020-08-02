#version 330 core

//vec3 sun_dir = vec3(1,1,0);

in vec3 fragPos;
in vec3 normalOut;
in vec3 cameraPosOut;
flat in int num_lights_out;
flat in vec3 lightsOut[10];


out vec3 color;
void main() {
    float ambient = 0.1;
    float diffuse = 0;
    float spec = 0;

    float specularStrength = 0.2;

    for (int i = 0; i < num_lights_out; i++) {
        vec3 fragToLight = lightsOut[i] - fragPos;

        diffuse += clamp( dot(normalOut, normalize(fragToLight)), 0, 1); 

        vec3 viewDir = normalize(cameraPosOut - fragPos);
        vec3 reflectView = normalize(reflect(viewDir, normalOut));
        spec += pow(max(dot(reflectView, normalize(fragToLight)), 0.0), 80);
    }

    diffuse = clamp(diffuse, 0, 1) * 0.7;
    spec = clamp(spec, 0, 1) * 0.3;

    color = vec3(0.5,0.7,0.9) * clamp(diffuse + ambient + spec * specularStrength, 0, 1);
}
