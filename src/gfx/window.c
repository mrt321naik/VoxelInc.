#include <include/VX/gfx.h>

static u8 VXGlewInit = 0;

GLFWwindow* VXNewWindow(u32 width, u32 height, char* title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) return NULL;

    glfwMakeContextCurrent(window);
    if (!VXGlewInit) {
        if (glewInit() != GLEW_OK) {
            glfwDestroyWindow(window);
            return NULL;
        } VXGlewInit = 1;
    }

    return window;
}

VXResult VXDelWindow(GLFWwindow* window) {
    if (!window) return VX_ERROR;
    glfwDestroyWindow(window);
    return VX_OK;
}
