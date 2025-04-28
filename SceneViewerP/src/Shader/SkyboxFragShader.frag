#version 410 core

out vec4 fragColor;

in vec3 texCoord;

uniform samplerCube skybox;

void main(){
	fragColor = texture(skybox, texCoord);
}