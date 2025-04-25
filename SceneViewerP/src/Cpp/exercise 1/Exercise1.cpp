#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"


//Creating 2 different triangles using different vao's and different colors using different shaders

int main()
{


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 600);

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Load OpenGL functions from GPU to use it in c++
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"  //we say that from vertex attributes in index 0 (which is position), i assign it to aPos
        "void main(){\n"
        "gl_Position = vec4(aPos, 1.0);\n"
        "}";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
        "}";

    const char* fragmentShaderSource2 = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "FragColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
        "}";

    //Creating vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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

    //Creating fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }

    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);


    //Creating a shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); //Created a program in gpu for shader

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();

    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);


    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader2);


    float vertices[] = {
        -0.5f, 0.5f, 0.0f,
        -1.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1.0f, -0.5f, 0.0f
    };
    unsigned int indices[] = { // note that we start from 0!
        0, 1, 2, // first triangle
        2, 3, 4 // second triangle
    };


    unsigned int VAO, VBO; //can store position, color, texture...)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); //It allocates its ID in GPU

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind c++ vbo and gpu vbo (which we created in vram)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Specify indexes for vertex shader to divide
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //saying shader that first 3 elements will be position datas
    glEnableVertexAttribArray(0); //Enables vertexAttrib at index 0 (normally disabled)

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VAO2, VBO2; //can store position, color, texture...)
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2); //It allocates its ID in GPU

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2); //Bind c++ vbo and gpu vbo (which we created in vram)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Specify indexes for vertex shader to divide
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //saying shader that first 3 elements will be position datas
    glEnableVertexAttribArray(0); //Enables vertexAttrib at index 0 (normally disabled)

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO); //Bind c++ vbo and gpu vbo (which we created in vram)

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //Draw function for ebo's

        glUseProgram(shaderProgram2);

        glBindVertexArray(VAO2); //Bind c++ vbo and gpu vbo (which we created in vram)

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int))); //Draw function for ebo's


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}