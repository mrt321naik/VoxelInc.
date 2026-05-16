#include "core/core.c"
#include "math/math.c"
#include "gfx/gfx.c"

void VXExitCallback(GLFWwindow* window) {
    glfwSetWindowShouldClose(window, 1);
}

// TODO: this should probably be an actual VXMouse struct :| ~@zafflins
static u8 firstMouse = 1;
static f32 lastX = 640.0f;
static f32 lastY = 360.0f;
static f32 sensitivity = 0.0025f;
void VXCursorCallback(GLFWwindow* window, double xpos, double ypos) {
    VXCamera* cam = glfwGetWindowUserPointer(window);
    if (!cam) return;

    if (firstMouse) {
        lastX = (f32)xpos;
        lastY = (f32)ypos;
        firstMouse = 0;
    }

    f32 xoffset = (f32)xpos - lastX;
    f32 yoffset = lastY - (f32)ypos; // inverted Y

    lastX = (f32)xpos;
    lastY = (f32)ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam->angle.x += yoffset; // pitch
    cam->angle.y += xoffset; // yaw

    f32 max = TO_RADIANS(89);
    cam->angle.x = CLAMP(cam->angle.x, -max, max);
}

// TODO: hardcoded shaders? check. ~@zafflins
const char* vertex =
    "#version 450 core\n"
    "layout (location = 0) in ivec3 aPos;\n"
    "layout (location = 1) in int type;\n"
    "layout (location = 2) in int face;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 proj;\n"
    "void main() {\n"
    "gl_Position = proj * view * model * vec4(aPos, 1.0);\n"
    "}"
;

const char* fragment =
    "#version 450 core\n"
    "out vec4 frag;\n"
    "void main() {\n"
    "frag = vec4(1.0, 0.5, 0.8, 1.0);\n"
    "}"
;

int main() {
    if (!glfwInit()) return 1;

    VXScene scene = {0};
    VXNewScene(VXNewVec3(1, 2, 1), &scene);

    GLFWwindow* window = VXNewWindow(1280, 720, "Voxel Inc");
    VXNewInputCallback(VXExitCallback, GLFW_KEY_ESCAPE);
    glfwSetCursorPosCallback(window, VXCursorCallback);

    VXCamera camera = {0};
    VXNewCamera(window, &camera);

    u32 shader = VXNewShader(vertex, fragment);

    VXChunk* chunk = VXGetChunk(VXNewVec3(0, 0, 0), &scene);
    VXGetChunk(VXNewVec3(0, 1, 0), &scene);
    FOR_I(0, 32, 1) {
        FOR_J(0, 32, 1) {
            FOR_K(0, 32, 1) {
                chunk->data[i * 32 * 32 + j * 32 + k] = i + j + k;
            }
        }
    }

    u8 wireframe = 0;
    VXArena arena = {0};
    VXNewArena(100 * MiB, &arena);
    VXBuildChunk(chunk, &arena);

    while (!glfwWindowShouldClose(window)) {
        VXBegin(&camera);

        VXRunInputCallbacks(window);
        if (VXKeyPressed(GLFW_KEY_A, window)) {
            VXMoveCameraLeft(&camera);
        } if (VXKeyPressed(GLFW_KEY_D, window)) {
            VXMoveCameraRight(&camera);
        } if (VXKeyPressed(GLFW_KEY_W, window)) {
            VXMoveCameraForward(&camera);
        } if (VXKeyPressed(GLFW_KEY_S, window)) {
            VXMoveCameraBackward(&camera);
        } if (VXKeyPressed(GLFW_KEY_SPACE, window)) {
            VXMoveCameraUp(&camera);
        } if (VXKeyPressed(GLFW_KEY_LEFT_SHIFT, window)) {
            VXMoveCameraDown(&camera);
        }

        if (VXKeyPressed(GLFW_KEY_F1, window) && !wireframe) {
            wireframe = 1;
        } if (VXKeyPressed(GLFW_KEY_F2, window) && wireframe) {
            wireframe = 0;
        }

        if (wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        glUseProgram(shader);
        VXSetShaderUniform("model", &chunk->mesh.matrix.m, VX_UNIFORM_MAT4, shader);
        VXSetShaderUniform("view", &camera.view.m, VX_UNIFORM_MAT4, shader);
        VXSetShaderUniform("proj", &camera.proj.m, VX_UNIFORM_MAT4, shader);
        glBindVertexArray(chunk->mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, chunk->mesh.count);

        VXEnd(window);
    }

    VXDelArena(&arena);
    VXDelScene(&scene);
    VXDelWindow(window);
    glfwTerminate();
    return 0;
}
