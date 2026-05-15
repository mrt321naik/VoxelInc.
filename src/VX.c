#include "core/core.c"
#include "gfx/gfx.c"

int main() {
    if (!glfwInit()) return 1;

    GLFWwindow* window = VXNewWindow(1280, 720, "Voxel Inc");

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VXDelWindow(window);
    glfwTerminate();

    return 0;
}
