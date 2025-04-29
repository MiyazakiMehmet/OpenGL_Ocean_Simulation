#pragma once

#include <GL/glew.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <gtc/type_ptr.hpp>

class Light {
protected:
	float ambientIntensity, diffuseIntensity;
	glm::vec3 lightColor;
public:
	Light();
	Light(float ambIntensity, float difIntensity, glm::vec3 lightCol);

	void UseLight(unsigned int ambientIntensityUniformLoc, unsigned int diffuseIntensityUniformLoc, unsigned int lightColor);

	~Light();
};
