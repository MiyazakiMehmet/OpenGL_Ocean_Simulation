#version 410 core

out vec4 fragColor;

in vec3 texCoord;

uniform samplerCube skybox;
uniform vec3 sunDir;

void main(){

    vec3 viewDir = normalize(texCoord); // similar to fragPos - eyePos

    float align   = max(dot(viewDir, sunDir), 0.0);

    // soften the falloff so you can actually see it
    float sunDisk = pow(align, 1500.0);                    
    float sunHalo = smoothstep(1.0, 1.0, align);

    vec3 sunColor = vec3(1.0,0.8,0.4);
    vec3 sunTerm  = sunColor * (sunDisk * 1.0 + sunHalo * 0.5);

    // Simulate vertical distance to horizon using viewDir.y
    float fakeDist = 1.0 - abs(viewDir.y);  // 1 near horizon, 0 straight up/down

    float fogStart = 0.8;
    float fogEnd   = 1.0;
    float fogFactor = clamp((fogEnd - fakeDist) / (fogEnd - fogStart), 0.0, 1.0);

    vec3 fogColor = vec3(1.0); // white fog
    vec3 skyColor = texture(skybox, viewDir).rgb;

    vec3 finalColor = mix(fogColor, skyColor, fogFactor);
    finalColor += sunTerm;
    fragColor = vec4(finalColor, 1.0);
}