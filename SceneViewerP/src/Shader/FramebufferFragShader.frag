#version 330 core

out vec4 fragColor;
in vec2 texCoord;

uniform sampler2D screenTexture;

void main(){
	vec3 col = texture(screenTexture, texCoord).rgb;
	fragColor = vec4(col, 1.0); //Identifies that tex position and gets that textures pixel color
}