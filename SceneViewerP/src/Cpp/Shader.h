#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include <GL/glew.h>

#include "DirectionalLight.h"
#include "Material.h"

class Shader {
public:
	unsigned int shaderID;
	unsigned int vertexShader, fragmentShader;
	unsigned int modelUniformLoc, viewUniformLoc, projectionUniformLoc, timeUniformLoc,
		lightColorUniformLoc, lightAmbientIntensityLoc, lightDiffuseIntensityLoc, materialSpecularIntensityLoc, materialShininessLoc, lightDirectionUniformLoc, eyePosUniformLoc,
		sunLightDirUniformLoc;
public:
	Shader();

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void CompileShader(std::string& vertexCodePath, std::string& fragmentCodePath);

	//File handling
	std::string ReadFile(std::string& filePath);

	//Get Uniform Location
	unsigned int GetModelUniformLoc();
	unsigned int GetViewUniformLoc();
	unsigned int GetProjectionUniformLoc();
	unsigned int GetTimeUniformLoc();
	unsigned int GetEyePosUniformLoc();
	unsigned int GetLightDirUniformLoc();
	unsigned int GetSunLightDirUniformLoc();


	void UseShader();

	void SetDirectionalLight(DirectionalLight directionalLight);
	void SetMaterial(Material material);


	~Shader();
};