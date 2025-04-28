#pragma once

#include "stb_image.h"

#include <iostream>
#include <vector>
#include <string>

#include "GL/glew.h"

class Texture {
private:
	unsigned int textureID;
	int width, height, nrChannels;
	const char* texPath;
	unsigned char* texData;
	std::vector<std::string> cubeFacesPath;
	bool isCubeMap = false;

public:
	Texture();
	Texture(const char* texturePath);
	Texture(std::vector<std::string>& faces);


	void CompileTexture();
	unsigned int CompileCubeMap();
	void UseTexture();

	~Texture();
};