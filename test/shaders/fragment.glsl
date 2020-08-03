#version 330 core

//vec3 sun_dir = vec3(1,1,0);

in vec3 fragPos;
in vec3 normalOut;
flat in vec3 cameraPosOut;
flat in int num_lights_out;
flat in vec3 lightsOut[10];

flat in vec3 sunPositionOut;
flat in int sunExistsOut;

vec2 calcSun(vec3 sunPos) {
    vec3 fragToSun = sunPos - fragPos;

    float diffuse = clamp( dot(normalOut, normalize(fragToSun)), 0, 1);

    vec3 viewDir = normalize(cameraPosOut - fragPos);
    vec3 reflectView = normalize(reflect(viewDir, normalOut));
    float spec = pow(max(dot(reflectView, normalize(fragToSun)), 0.0), 80);

    return vec2(diffuse, spec);
}

vec2 calcLight(vec3 lightPos) {
    vec3 fragToLight = lightPos - fragPos;
    float strength_sqr = dot(fragToLight, fragToLight);
    float strength = inversesqrt(strength_sqr) * 35;

    float diffuse = clamp( dot(normalOut, normalize(fragToLight)), 0, 1) * strength; 

    vec3 viewDir = normalize(cameraPosOut - fragPos);
    vec3 reflectView = normalize(reflect(viewDir, normalOut));
    float spec = pow(max(dot(reflectView, normalize(fragToLight)), 0.0), 80) / strength_sqr / 30;

    return vec2(diffuse, spec);
}


out vec3 color;
void main() {
    float ambient = 0.1;
    float diffuse = 0;
    float spec = 0;

    float specularStrength = 0.2;

    if (sunExistsOut == 1) {
        vec2 sunValues = calcSun(sunPositionOut);
        diffuse += sunValues[0];
        spec += sunValues[1];
    }

    for (int i = 0; i < num_lights_out; i++) {
        vec2 lightValues = calcLight(lightsOut[i]);
        diffuse += lightValues[0] * 0.3;
        spec += lightValues[1] * 0.3;
    }

    diffuse = clamp(diffuse, 0, 1) * 0.7;
    spec = clamp(spec, 0, 1) * 0.3;

    color = vec3(0.5,0.7,0.9) * clamp(diffuse + ambient + spec * specularStrength, 0, 1);
}
