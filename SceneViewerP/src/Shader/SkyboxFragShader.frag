#version 410 core

out vec4 fragColor;

in vec3 texCoord;

uniform samplerCube skybox;

void main(){

    vec3 viewDir = normalize(texCoord); // similar to fragPos - eyePos

    // Simulate vertical distance to horizon using viewDir.y
    float fakeDist = 1.0 - abs(viewDir.y);  // 1 near horizon, 0 straight up/down

    float fogStart = 0.8;
    float fogEnd   = 1.0;
    float fogFactor = clamp((fogEnd - fakeDist) / (fogEnd - fogStart), 0.0, 1.0);

    vec3 fogColor = vec3(1.0); // white fog
    vec3 skyColor = texture(skybox, viewDir).rgb;

    vec3 finalColor = mix(fogColor, skyColor, fogFactor);
    fragColor = vec4(finalColor, 1.0);
}