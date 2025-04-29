#pragma once
#include "Light.h"

class DirectionalLight : Light {
private:
	glm::vec3 lightDirection;
public:
	DirectionalLight();
	DirectionalLight(float ambIntensity, float difIntensity, glm::vec3 lightCol,
		glm::vec3 lightDir);

	void UseLight(unsigned int ambientIntensityUniformLoc, unsigned int diffuseIntensityUniformLoc, unsigned int lightColor,
		unsigned int lightDirLoc);
};
