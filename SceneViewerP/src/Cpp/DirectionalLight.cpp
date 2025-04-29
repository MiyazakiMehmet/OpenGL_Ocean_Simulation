#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
	: Light()
{
	lightDirection = glm::vec3(-0.2, -0.4, -0.1);
}

DirectionalLight::DirectionalLight(float ambIntensity, float difIntensity, glm::vec3 lightCol, glm::vec3 lightDir)
	: Light(ambIntensity, difIntensity, lightCol)
{
	lightDirection = lightDir;
}

void DirectionalLight::UseLight(unsigned int ambientIntensityUniformLoc, unsigned int diffuseIntensityUniformLoc, unsigned int lightColor, unsigned int lightDirLoc)
{
	Light::UseLight(ambientIntensityUniformLoc, diffuseIntensityUniformLoc, lightColor);
	glUniform3f(lightDirLoc, lightDirection.x, lightDirection.y, lightDirection.z);
}
