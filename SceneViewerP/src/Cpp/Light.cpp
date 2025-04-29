#include "Light.h"

Light::Light()
{
	ambientIntensity = 0.4;
	diffuseIntensity = 0.4;
	lightColor = glm::vec3(1.0, 1.0, 1.0);
}

Light::Light(float ambIntensity, float difIntensity, glm::vec3 lightCol)
{
	ambientIntensity = ambIntensity;
	diffuseIntensity = difIntensity;
	lightColor = lightCol;
}

void Light::UseLight(unsigned int ambientIntensityUniformLoc, unsigned int diffuseIntensityUniformLoc, unsigned int lightColorUniformLoc)
{
	glUniform1f(ambientIntensityUniformLoc, ambientIntensity);
	glUniform1f(diffuseIntensityUniformLoc, diffuseIntensity);
	glUniform3f(lightColorUniformLoc, lightColor.x, lightColor.y, lightColor.z);
}

Light::~Light()
{
}
