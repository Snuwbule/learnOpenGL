#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "windowHandling.h"

int main() {
    glfwInit();
    // define OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // apple OpenGL support
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create OpenGL window
    // Because we needed a window to render silly
    GLFWwindow* window = glfwCreateWindow(800, 600, "Pain and suffering", NULL, NULL);

    // window creation error handling
    if (window == NULL) {
        std::cerr << "ERROR: Failed Creating GLFW window\n";
        glfwTerminate();
        return -1;
    }
    
    // Create OpenGL context after finished creating window
    glfwMakeContextCurrent(window);
    
    // GLAD stuff
    gladLoadGL();
    glfwSetFramebufferSizeCallback(window, winHandle::frame_buffer_size_callback);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    }; 

    //create Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //Vertex shader
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    //Vertex Shader Compile
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Vertex Shader compile error
    int* success = new int;
    char* infoLog = new char[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //Clean Up
    delete success;
    delete[] infoLog;

    // fragment shader
    const char* fragShadSrc = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShadSrc, NULL);
    glCompileShader(fragmentShader);

    //Fragment shader compile error
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //Clean up and make success and info log nullptr
    delete success;
    delete[] infoLog;
    success = nullptr;
    infoLog = nullptr;

    //Create Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glfwSwapInterval(1);
    // Main render loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07, 0.13, 0.17, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
