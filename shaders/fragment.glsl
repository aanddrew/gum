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

    float specularStrength = 0.3;
    vec3 viewDir = normalize(cameraPosOut - fragPos);
    vec3 reflectView = normalize(reflect(viewDir, normalOut));
    float spec = pow(max(dot(reflectView, normalize(fragToLight)), 0.0), 32);

    //vec3 reflectDir = normalize(reflect(normalize(-fragToLight), normalOut));

    color = vec3(1,1,1) * clamp(diffuse + ambient + spec * specularStrength, 0, 1);
}
