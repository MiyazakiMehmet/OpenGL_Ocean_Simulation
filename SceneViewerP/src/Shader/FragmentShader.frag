#version 330 core

out vec4 FragColor;
in vec2 texCoord;
in float waveHeight;
in vec3 fragNormal;

uniform sampler2D ourTexture;
uniform float time;
uniform vec3 lightDir;

void main(){

vec4 waterColor = texture(ourTexture, texCoord * 4.0);
vec3 lightning;

//Ambient light
float ambientFactor = 0.1;
vec3 ambientLight = ambientFactor * vec3(1.0, 1.0, 1.0); //it turns vec3(0.3, 0.3, 0.3) still white but darker

//Diffuse light
float diffuseFactor = max(dot(normalize(-lightDir), normalize(fragNormal)), 0); //changing lightDir since it must be towards normal, and dot product find difference in angle to change light intensity
vec3 diffuseLight = diffuseFactor * vec3(1.0, 1.0, 1.0);

lightning = ambientLight + diffuseLight;

//Water texture affected by lightning
vec4 waterLit = vec4(lightning, 1.0) * waterColor;

float foamAmount = clamp((waveHeight + 0.1) * 1.4, 0.0, 1.0);

vec4 foamColor = vec4(1.0, 1.0, 1.0, 1.0); //White foam

//Blend water texture with foam
FragColor = mix(waterLit, foamColor, foamAmount);
};