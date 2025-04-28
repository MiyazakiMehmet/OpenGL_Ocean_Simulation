#version 410 core

layout (location = 0) in vec3 aPos;

out vec3 texCoord;

uniform mat4 view;
uniform mat4 projection;

void main(){
	texCoord = aPos;
	vec4 pos = projection * view * vec4(aPos, 1.0);
	gl_Position = pos.xyww; // trick: set depth to 1.0
}