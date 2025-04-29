#pragma once

#include <GL/glew.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <gtc/type_ptr.hpp>

class Material
{
private:
	float specularIntensity;
	float shininess;
public:
	Material();
	Material(float specIntensity, float shine);

	void UseMaterial(unsigned int specularIntensityUniformLoc, unsigned int shininessUniformLoc);

	~Material();
};

