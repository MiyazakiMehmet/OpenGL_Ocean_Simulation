#include "Shader.h"


Shader::Shader()
{
	shaderID = 0;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);

	//Error handling
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	//Attach to shaders to program
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
	}

	//Uniforms

}

void Shader::CompileShader(std::string& vertexCodePath, std::string& fragmentCodePath)
{
	std::string vertexCodeStr = ReadFile(vertexCodePath);
	std::string fragmentCodeStr = ReadFile(fragmentCodePath);

	const char* vertexCode = vertexCodeStr.c_str();
	const char* fragmentCode = fragmentCodeStr.c_str();

	//Vertex Shader Compile
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);

	//Error handling
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	//Fragment Shader Compile
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);

	//Error Handling
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	//Creating the Shader Program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	//Does not need seperate shader since its already linked
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Error Handling
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
	}

	//Getting uniforms Locations
	modelUniformLoc = glGetUniformLocation(shaderID, "model");
	viewUniformLoc = glGetUniformLocation(shaderID, "view");
	projectionUniformLoc = glGetUniformLocation(shaderID, "projection");
	timeUniformLoc = glGetUniformLocation(shaderID, "time");
	lightColorUniformLoc = glGetUniformLocation(shaderID, "directionalLight.base.color");
	lightAmbientIntensityLoc = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	lightDiffuseIntensityLoc = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	materialSpecularIntensityLoc = glGetUniformLocation(shaderID, "material.specularIntensity");
	materialShininessLoc = glGetUniformLocation(shaderID, "material.shininess");
	lightDirectionUniformLoc = glGetUniformLocation(shaderID, "directionalLight.lightDir");
	eyePosUniformLoc = glGetUniformLocation(shaderID, "eyePos");
	sunLightDirUniformLoc = glGetUniformLocation(shaderID, "sunDir");



}

std::string Shader::ReadFile(std::string& filePath)
{
	std::ifstream file(filePath);
	std::stringstream buffer;

	if (!file.is_open()) {
		std::cout << "Failed to open file:" << filePath << std::endl;

		return "";
	}
	buffer << file.rdbuf(); //Read and store entire file into string stream
	file.close();

	return buffer.str(); //Transform string and then c-style string

}

unsigned int Shader::GetModelUniformLoc()
{
	return modelUniformLoc;
}

unsigned int Shader::GetViewUniformLoc()
{
	return viewUniformLoc;
}

unsigned int Shader::GetProjectionUniformLoc()
{
	return projectionUniformLoc;
}

unsigned int Shader::GetTimeUniformLoc()
{
	return timeUniformLoc;
}

unsigned int Shader::GetEyePosUniformLoc()
{
	return eyePosUniformLoc;
}

unsigned int Shader::GetLightDirUniformLoc()
{
	return lightDirectionUniformLoc;
}

unsigned int Shader::GetSunLightDirUniformLoc()
{
	return sunLightDirUniformLoc;
}


void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::SetDirectionalLight(DirectionalLight directionalLight)
{
	directionalLight.UseLight(lightAmbientIntensityLoc, lightDiffuseIntensityLoc, lightColorUniformLoc, lightDirectionUniformLoc);
}

void Shader::SetMaterial(Material material)
{
	material.UseMaterial(materialSpecularIntensityLoc, materialShininessLoc);
}

Shader::~Shader() {
	glDeleteProgram(shaderID);
}
