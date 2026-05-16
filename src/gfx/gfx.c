#include "gl.c"
#include "window.c"
#include "camera.c"

void VXBegin(VXCamera* c) {
    VXClearColor(10, 10, 15, 255);
    VXComputeCameraVectors(c);
    VXComputeCameraView(c);
}

void VXEnd(GLFWwindow* window) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
