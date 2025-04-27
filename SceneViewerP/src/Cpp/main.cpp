#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <gtc/type_ptr.hpp>


#include "Shader.h"

//Camera attributes
glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 worldUp;
glm::vec3 cameraRight;
glm::vec3 cameraUp;
float cameraSpeed;
float deltaTime = 0.0f;
float currentFrame;
float lastFrame = 0.0f;
//pitch&yaw
bool firstMouse = true;
double previousX = 700; //Center of the viewport
double previousY = 500; //Center of the viewport
float pitch;
float yaw = -90; //Since OpenGL starts z from -z



void MouseCallback(GLFWwindow* window, double xPos, double yPos) {
    if (firstMouse) {
        previousX = xPos;
        previousY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - previousX;
    float yOffset = previousY - yPos;

    previousX = xPos;
    previousY = yPos;

    float sensivity = 0.2f;
    xOffset *= sensivity;
    yOffset *= sensivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)); //Change in yaw and pitch affects x-axis
    direction.y = glm::sin(glm::radians(pitch)); //Change in pitch affects y-axis
    direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch)); //Change in yaw and pitch affects z-axis

    //Update camera directions
    cameraFront = glm::normalize(direction); //Camera front is direction which camera looks
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp)); //Yaw is changed so new right(x-axis) is changed too, so update it
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void ProcessInput(GLFWwindow* window) {

    //Delta time = time between current frame and last frame  
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += deltaTime * cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= deltaTime * cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= deltaTime * cameraRight * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += deltaTime * cameraRight * cameraSpeed;

    
}

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1400, 1000, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 1400, 1000);

    //Handling yaw/pitch
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, MouseCallback);

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Load OpenGL functions from GPU to use it in c++
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    Shader shader;

    //Creating vertices(dots that have vertex attributes)
    std::vector<float> vertices;
    
    int gridSize = 400; //100x100
    float size = 40.0f; //We strect the vertex position to make bigger triangles
    for (int y = 0; y <= gridSize; y++) {  //Creating vertices vertically (e.g. y=0,1,2,3,4,5..., x=0)
        for (int x = 0; x <= gridSize; x++) {  //Creating vertices horizantaly (e.g. y=0, x=0,1,2,3,4,5...)
            //Vertex position attributes
            float xPos = ((float)x / gridSize) * size - size / 2.0f;
            float yPos = 0.0f;
            float zPos = ((float)y / gridSize) * size - size / 2.0f;
            //Vertex texture position attributes
            float uPos = ((float)x / gridSize);
            float vPos = ((float)y / gridSize);

            vertices.push_back(xPos);
            vertices.push_back(yPos);
            vertices.push_back(zPos);
            vertices.push_back(uPos);
            vertices.push_back(vPos);
            //Vector will be (0,0,0,0,0),(1,0,0,1,0),(2,0,0,2,0)...

        }
    }

    unsigned int VAO, VBO; //can store position, color, texture...)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); //It allocates its ID in GPU

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind c++ vbo and gpu vbo (which we created in vram)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    //Specify indexes for vertex shader to divide
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //saying shader that first 3 elements will be position datas
    glEnableVertexAttribArray(0); //Enables vertexAttrib at index 0 (normally disabled)

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); //Enables vertexAttrib at index 0 (normally disabled)

    //Creating indices
    std::vector<unsigned int> indices;

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            //Creating Rectangle
            int i0 = y * (gridSize + 1) + x;
            int i1 = i0 + 1;
            int i2 = i0 + (gridSize + 1);
            int i3 = i2 + 1;

            //First Triangle
            indices.push_back(i0);
            indices.push_back(i2);
            indices.push_back(i1);
            //Second Triangle
            indices.push_back(i1);
            indices.push_back(i2);
            indices.push_back(i3);

        }
    }

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0); // Unbind

    //Transformations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.5f, -1.0f, 0.0f));
    //model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    //Camera(view matrix)
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); //Where camera stands
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); //Direction, Where the point camera looks (-1 since it points z axis)
    
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    //Order matters, our right vector must be recalculated relative to cameraFront since it changes when pitch/yaw changes
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp)); //We want to retrieve cameraRight so we take cross product of y and z it gives perpendicular x direction relative to camera
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront)); //We want to retrieve cameraUp so we take cross product of x and z it gives perpendicular y direction relative to camera

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    cameraSpeed = 2.5f;

    //Projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

    //Textures
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("src/Textures/ocean.png", &width, &height, &nrChannels, 0);
    //std::cout << "Texture loaded with channels: " << nrChannels << std::endl;

    if (data) {
        GLenum format = GL_RGB; //by default
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //Lightning
    glm::vec3 directionalLight = glm::vec3(-0.2f, -0.3f, -0.3f);

    //Shader 

    std::string vertexShaderPath = "src/Shader/VertexShader.vert";
    std::string fragmentShaderPath = "src/Shader/FragmentShader.frag";

    shader.CompileShader(vertexShaderPath, fragmentShaderPath);

    //Getting uniforms Locations
    unsigned int modelUniformLoc = shader.UniformLocation("model");
    unsigned int viewUniformLoc = shader.UniformLocation("view");
    unsigned int projectionUniformLoc = shader.UniformLocation("projection");
    unsigned int timeUniformLoc = shader.UniformLocation("time");
    unsigned int lightDirectionUniformLoc = shader.UniformLocation("lightDir");



    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);   
        
        //Handling keys for camera
        ProcessInput(window);

        //Update view matrix if camera movement changes
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        shader.UseShader();

        //Adding data to uniforms after creating shaders
        glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewUniformLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionUniformLoc, 1, GL_FALSE, glm::value_ptr(projection));
        //For wave
        float timeValue = glfwGetTime();
        glUniform1f(timeUniformLoc, timeValue);
        //For light
        glUniform3fv(lightDirectionUniformLoc, 1, glm::value_ptr(directionalLight));


        //Binding texture and vao
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO); //Bind c++ vbo and gpu vbo (which we created in vram)

        //Drawing(connecting vertices(dots))
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); //Draw function for ebo's


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}

