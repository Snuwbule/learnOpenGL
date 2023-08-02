#include <fstream>
#include <iostream>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "windowHandling.h"
#include "platformHandling/errorOutput.h"

const GLchar* readGLSL(const char* filePath) {
	std::ifstream shader(filePath);
	if (!shader.is_open()) {
		outputError("Couldn't Open GLSL File.", true);
		shader.clear();
		shader.close();
		return "";
	}

	shader.seekg(0, std::ios::end);
	size_t length = shader.tellg();
	shader.seekg(0, std::ios::beg);

	char* buffer = new char[length + 1];
	shader.read(buffer, length);
	buffer[length] = '\0';

	shader.clear();
	shader.close();
	const GLchar* fileContent = buffer;
	delete buffer;
	buffer = nullptr;
	return fileContent;
}

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

    //Vertex shader
	const GLchar* vertexShaderSource = readGLSL("shaders/VertexShader.glsl");

    //Vertex Shader Compile
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
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

    // fragment shader
    const GLchar* fragShadSrc = readGLSL("shaders/fragmentShader.glsl");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShadSrc, NULL);
    glCompileShader(fragmentShader);

    //Fragment shader compile error
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Create Shader Program
	GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, success);

    if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    //Clean Up
    delete success;
    delete[] infoLog;
    success = nullptr;
    infoLog = nullptr;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(shaderProgram);


	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	//create Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//Create Vertex Array Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	

    // Main render loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07, 0.13, 0.17, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
        glfwSwapBuffers(window);

    }

	glDeleteProgram(vertexShader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
