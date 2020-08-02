#version 330 core

//vec3 sun_dir = vec3(1,1,0);

in vec3 fragPos;
in vec3 lightPos;
in vec3 normalOut;
in vec3 cameraPosOut;

out vec3 color;
void main() {
    vec3 fragToLight = lightPos - fragPos;

    float ambient = 0.1;
    float diffuse = clamp( dot(normalOut, normalize(fragToLight)), 0, 1); 

    float specularStrength = 0.0;
    vec3 viewDir = normalize(cameraPosOut - fragPos);
    vec3 reflectView = normalize(reflect(viewDir, normalOut));
    float spec = pow(max(dot(reflectView, normalize(fragToLight)), 0.0), 80);

    color = vec3(0.5,0.7,0.9) * clamp(diffuse + ambient + spec * specularStrength, 0, 1);
}
