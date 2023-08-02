#include "windowHandling.h"

namespace winHandle {
    void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0,0,width, height);
    }
}
