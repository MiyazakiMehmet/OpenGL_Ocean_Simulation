#pragma once

#include "stb_image.h"

#include <iostream>
#include <vector>

#include "GL/glew.h"

class Texture {
private:
	unsigned int textureID;
	int width, height, nrChannels;
	const char* texPath;
	unsigned char* texData;
public:
	Texture();
	Texture(const char* texturePath);

	void CompileTexture();
	void UseTexture();

	~Texture();
};