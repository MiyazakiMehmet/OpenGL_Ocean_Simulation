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

    void main() {
        vec3 pos = aPos;

        float wave = 0.0;
        float dX = 0.0;
        float dZ = 0.0;

        for (int i = 0; i < 32; ++i) {
            vec2 dir = uWaveDirs[i];
            float amp = uAmplitudes[i];
            float freq = uFrequencies[i];
            float phaseSpeed = uPhases[i];

            float phi = dot(dir, pos.xz) * freq + time * phaseSpeed * 1.3;
            float sinVal = sin(phi);
            float env = exp(sinVal - 1.0);  // envelope

            
            wave += amp * env;

            float dEnv = env * cos(phi);
            float d = amp * dEnv * freq;
            dX += d * dir.x;
            dZ += d * dir.y;
        }

        pos.y += wave;
        waveHeight = pos.y;

        // Recompute normal
        vec3 normal = normalize(vec3(-dX, 1.0, -dZ));
        fragNormal = normalize(mat3(model) * normal);

        fragPos = vec3(model * vec4(pos, 1.0));
        gl_Position = projection * view * vec4(fragPos, 1.0);
    }
