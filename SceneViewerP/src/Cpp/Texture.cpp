#include "Texture.h"

Texture::Texture()
{
	textureID = 0;
	width = 0, height = 0, nrChannels = 0;
	texPath = "";
}

Texture::Texture(const char* texturePath)
{
	textureID = 0;
	width = 0, height = 0, nrChannels = 0;
	texPath = texturePath;
}

void Texture::CompileTexture()
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texData = stbi_load(texPath, &width, &height, &nrChannels, 0);
	if (!texData) {
		std::cout << "Failed to load texture" << std::endl;
	}

	GLenum format = (nrChannels = 3) ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, texData);

	stbi_image_free(texData);
}

void Texture::UseTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	nrChannels = 0;
	texPath = "";
}
