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
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, -0.0f * float(sqrt(3)) / 2, 0.0f
    };

    
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
