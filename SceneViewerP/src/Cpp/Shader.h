#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include <GL/glew.h>

class Shader {
private:
	unsigned int shaderID;
	unsigned int vertexShader, fragmentShader;
public:
	Shader();

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void CompileShader(std::string& vertexCodePath, std::string& fragmentCodePath);

	//File handling
	std::string ReadFile(std::string& filePath);

	void UseShader();

	//Uniform
	unsigned int UniformLocation(const char* uniformName);

	~Shader();
};