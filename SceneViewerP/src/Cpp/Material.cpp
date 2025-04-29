#include "Material.h"

Material::Material()
{
	specularIntensity = 0.4f;
	shininess = 10.0f;
}

Material::Material(float specIntensity, float shine)
{
	specularIntensity = specIntensity;
	shininess = shine;
}

void Material::UseMaterial(unsigned int specularIntensityUniformLoc, unsigned int shininessUniformLoc)
{
	glUniform1f(specularIntensityUniformLoc, specularIntensity);
	glUniform1f(shininessUniformLoc, shininess);
}

Material::~Material()
{
}
