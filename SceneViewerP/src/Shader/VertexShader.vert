#version 330 core

layout (location = 0) in vec3 aPos;  //we say that from vertex attributes in index 0 (which is position), i assign it to aPos
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;
out float waveHeight;
out vec3 fragNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;


void main(){
vec3 pos = aPos;

float wave = 0.0;	


// Basic wave 1 (x direction)
wave += sin(pos.x * 1.0 + time * 1.0) * 0.1;

// Basic wave 2 (z direction)
wave += cos(pos.z * 1.0 + time * 1.0) * 0.1;

// Additional wave 3 (diagonal movement)
wave += sin((pos.x + pos.z) * 0.6 + time * 0.7) * 0.08;

// Additional wave 4 (different frequency and slower)
wave += cos((pos.x * 0.2 + pos.z * 0.2) * 10.0 + time * 0.3) * 0.05;

pos.y += wave;

//Instead of using real normals, we'll use fake normals(estimated)
// Calculate derivatives
float dWave_dx = 0.0;
float dWave_dz = 0.0;

// Wave 1
dWave_dx += cos(pos.x * 1.0 + time * 1.0) * 1.0 * 0.1;

// Wave 2
dWave_dz += -sin(pos.z * 1.0 + time * 1.0) * 1.0 * 0.1;

// Wave 3
dWave_dx += cos((pos.x + pos.z) * 0.6 + time * 0.7) * 0.6 * 0.08;
dWave_dz += cos((pos.x + pos.z) * 0.6 + time * 0.7) * 0.6 * 0.08;

// Wave 4
dWave_dx += -sin((pos.x * 0.2 + pos.z * 0.2) * 10.0 + time * 0.3) * (0.2 * 10.0) * 0.05;
dWave_dz += -sin((pos.x * 0.2 + pos.z * 0.2) * 10.0 + time * 0.3) * (0.2 * 10.0) * 0.05;

fragNormal = normalize(vec3(-dWave_dx, 1.0, -dWave_dz));

waveHeight = pos.y;
texCoord = aTexCoord;

gl_Position = projection * view * model * vec4(pos, 1.0);
};