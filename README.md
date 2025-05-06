# OpenGL Ocean Simulation

![Screenshot_40](https://github.com/user-attachments/assets/06df701c-5a27-4c14-ba73-f289e1e566df)

This project is a realistic ocean scene implemented in C++ and OpenGL, featuring:

	•	Gerstner wave simulation with 32 directional waves
	•	Physically based directional lighting
	•	Real-time reflections and specular highlights
	•	Dynamic skybox with white fog and fake sun
	•	Distance-based fog blending for atmospheric depth
	•	Custom post-processing with framebuffers

Features

	•	Wave Simulation: Realistic ocean surface using a sum of sinusoidal waves with varying amplitude, frequency, and direction.
	•	Lighting: Directional light simulates sunlight with ambient, diffuse, and specular components.
	•	Fog and Horizon Fade: Distant water and sky fade smoothly into fog, enhancing depth.
	•	Fake Sun: Sunlight is approximated using a dot product of the view and light direction, including halo and bloom-like effect.
	•	Skybox: Rendered with a cube map and integrated fog and sun logic.
	•	Post-Processing: Fullscreen quad rendering using a custom framebuffer for effects and future extension.

Technologies Used

	•	C++
	•	OpenGL (GLSL shaders, framebuffers, VAO/VBO/EBO)
	•	GLFW & GLEW
	•	GLM for matrix math
	•	Custom lighting and material system

Build Instructions

Make sure you have:
	•	OpenGL 3.3+
	•	GLFW
	•	GLEW
	•	CMake (optional)

Clone the repo, include the texture and shader folders, and build using your preferred compiler.

```
g++ main.cpp -lglfw -lGLEW -lGL -o OceanSim
./OceanSim
```

