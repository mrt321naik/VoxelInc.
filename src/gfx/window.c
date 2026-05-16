#include "include/VX/def.h"
#include <include/VX/VX.h>


static u8 VXGlewInit = 0;

static u8 InputCallbackCount = 0;
static VXInputCallback InputCallbacks[255] = {0};

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

    glEnable(GL_CULL_FACE);

    return window;
}

VXResult VXDelWindow(GLFWwindow* window) {
    if (!window) return VX_ERROR;
    glfwDestroyWindow(window);
    return VX_OK;
}

u32 VXKeyPressed(i32 key, GLFWwindow* window) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

u32 VXKeyHeld(i32 key, GLFWwindow* window) {
    return glfwGetKey(window, key) == GLFW_REPEAT;
}

u32 VXButtonPressed(i32 button, GLFWwindow* window) {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

u32 VXButtonHeld(i32 button, GLFWwindow* window) {
    return glfwGetMouseButton(window, button) == GLFW_REPEAT;
}

VXResult VXNewInputCallback(void (*func)(GLFWwindow* window), i32 key) {
    if (InputCallbackCount >= 255) return VX_ERROR;
    InputCallbacks[InputCallbackCount++] = (VXInputCallback){.func = func, .key = key};
    return VX_OK;
}

void VXRunInputCallbacks(GLFWwindow* window) {
    FOR_I(0, InputCallbackCount, 1) {
        VXInputCallback* cb = &InputCallbacks[i];
        if (glfwGetKey(window, cb->key) == GLFW_PRESS) cb->func(window);
    }
}

VXResult VXDelInputCallback(i32 key) {
    FOR_I(0, InputCallbackCount, 1) {
        if (InputCallbacks[i].key == key) {
            InputCallbacks[i] = InputCallbacks[--InputCallbackCount];
            return VX_OK;
        }
    } return VX_ERROR;
}
