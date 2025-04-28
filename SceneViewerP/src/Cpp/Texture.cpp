#include "Texture.h"

Texture::Texture()
{
	textureID = 0;
	width = 0, height = 0, nrChannels = 0;
	texPath = "";
	isCubeMap = false;
}

Texture::Texture(const char* texturePath)
{
	textureID = 0;
	width = 0, height = 0, nrChannels = 0;
	texPath = texturePath;
	isCubeMap = false;
}

Texture::Texture(std::vector<std::string>& faces)
{
	textureID = 0;
	width = 0, height = 0, nrChannels = 0;
	texPath = "";
	cubeFacesPath = faces;
	isCubeMap = true;
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
		stbi_image_free(texData);
	}

	GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, texData);

	std::cout << "Loaded texture: " << texPath << " with " << nrChannels << " channels." << std::endl;

	stbi_image_free(texData);
}

unsigned int Texture::CompileCubeMap()
{
	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < cubeFacesPath.size(); i++) {
		texData = stbi_load(cubeFacesPath[i].c_str(), &width, &height, &nrChannels, 0);
		if (!texData) {
			std::cout << "Cubemap texture failed to load at path: " << cubeFacesPath[i] << std::endl;
			stbi_image_free(texData);

			return -1;
		}
		GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, texData); //First argument is enumerated

		std::cout << "Loaded texture: " << texPath << " with " << nrChannels << " channels." << std::endl;

		stbi_image_free(texData);
	}

	return textureID;
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	if (isCubeMap)
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	else
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
