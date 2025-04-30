#version 330 core

layout(location = 0) in vec3 aPos;

out float waveHeight;
out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

const int MAX_WAVES = 64;
uniform int   uNumWaves;
uniform vec2  uWaveDirs[MAX_WAVES];
uniform float uAmplitudes[MAX_WAVES];
uniform float uFrequencies[MAX_WAVES];
uniform float uPhases[MAX_WAVES];

// fBm helper functions
float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453123);
}

float noise2D(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    float a = hash(i);
    float b = hash(i + vec2(1, 0));
    float c = hash(i + vec2(0, 1));
    float d = hash(i + vec2(1, 1));
    vec2 u = f*f*(3.0 - 2.0*f);
    return mix(mix(a, b, u.x), mix(c, d, u.x), u.y);
}

float fbm(vec2 p) {
    float sum = 0.0;
    float amp = 1.0;
    float freq = 1.0;
    for (int i = 0; i < 5; ++i) {
        sum += amp * noise2D(p * freq);
        freq *= 2.0;
        amp *= 0.5;
    }
    return sum;
}

void main() {
    vec3 pos = aPos;

    float wave = 0.0;
    float dX = 0.0;
    float dZ = 0.0;

    for (int i = 0; i < uNumWaves; ++i) {
        vec2 dir = uWaveDirs[i];
        float amp = uAmplitudes[i];
        float freq = uFrequencies[i];
        float phaseSpeed = uPhases[i];

        float phi = dot(dir, pos.xz) * freq + time * 3.3;
        float sinVal = sin(phi);
        float env = exp(sinVal - 1.0);  // envelope

        wave += amp * env;

        float dEnv = env * cos(phi);
        float d = amp * dEnv * freq;
        dX += d * dir.x;
        dZ += d * dir.y;
    }

    // Add fBm for detail
    float detail = fbm(pos.xz * 3.0 + time * 0.2) * 0.02;
    pos.y += wave + detail;
    waveHeight = pos.y;

    // Recompute normal
    vec3 normal = normalize(vec3(-dX, 1.0, -dZ));
    fragNormal = normalize(mat3(model) * normal);

    fragPos = vec3(model * vec4(pos, 1.0));
    gl_Position = projection * view * vec4(fragPos, 1.0);
}
