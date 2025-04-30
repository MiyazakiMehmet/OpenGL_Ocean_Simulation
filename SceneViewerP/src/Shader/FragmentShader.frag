#version 330 core

out vec4 FragColor;
in  float waveHeight;
in  vec3  fragNormal;
in  vec3  fragPos;

struct Light {
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight {
    Light base;
    vec3  lightDir;
};

struct Material {
    float specularIntensity;
    float shininess;
};

uniform DirectionalLight directionalLight;
uniform Material         material;
uniform vec3             eyePos;

void main() {
    vec3 normalNormalized = normalize(fragNormal);
    vec3 lightDirNormalized = normalize(-directionalLight.lightDir);

    //Ambient Light
    vec3 ambient = directionalLight.base.ambientIntensity * directionalLight.base.color;

    //Diffuse Light
    float diffuseFactor = max(dot(normalNormalized, lightDirNormalized), 0.0); //We get dot product to find difference in degress and hold it above 0
    vec3 diffuse = directionalLight.base.diffuseIntensity * diffuseFactor * directionalLight.base.color;

    //Specular Light
    vec3 fragToEye = normalize(eyePos - fragPos);
    vec3 reflectedLight = reflect(-lightDirNormalized, normalNormalized);
    float specularFactor = pow(max(dot(fragToEye, reflectedLight), 0.0), material.shininess); //We get dot product of our eye relative to reflected light to find difference in degress and hoid it above 0
    vec3 specular = material.specularIntensity * specularFactor * directionalLight.base.color;

    // 4) tint water base blue, then add white specular
    vec3 waterBase = (ambient + diffuse) * vec3(0.0, 0.66, 1.0);
    vec3 finalColor  = waterBase + specular;

    FragColor = vec4(finalColor, 1.0);
}
