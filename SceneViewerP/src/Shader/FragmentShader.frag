#version 330 core

out vec4 FragColor;
in float waveHeight;
in vec3 fragNormal;

struct Light{
vec3 color;
float ambientIntensity;
float diffuseIntensity;
};

struct DirectionalLight{
Light base;
vec3 lightDir;
};

uniform sampler2D ourTexture;
uniform float time;
uniform DirectionalLight directionalLight;

vec3 CalculateDirectionalLight(Light light){

	//Ambient light
	vec3 ambientLight = light.ambientIntensity * light.color; //it turns vec3(0.3, 0.3, 0.3) still white but darker
	
	//Diffuse light
	float diffuseFactor = max(dot(normalize(-directionalLight.lightDir), normalize(fragNormal)), 0); //changing lightDir since it must be towards normal, and dot product find difference in angle to change light intensity
	vec3 diffuseLight = light.diffuseIntensity * diffuseFactor * light.color;
	
	return (ambientLight + diffuseLight);
}

void main(){

vec3 lightning = CalculateDirectionalLight(directionalLight.base);

//Water texture affected by lightning
vec4 waterLit = vec4(lightning, 1.0) * vec4(0.0,0.7,1.0,1.0);
FragColor = waterLit;
};