#include <include/VX/gfx.h>
#include <math.h>

VXResult VXNewCamera(GLFWwindow* window, VXCamera* camera) {
    if (!window || !camera) return VX_ERROR;

    camera->fov = 60.0f;
    camera->speed = 3e-3f;

    camera->pos = VXNewVec3(0.0f, 0.0f, 0.0f);
    camera->angle = VXNewVec3(0.0f, 0.0f, 0.0f);

    camera->up = VXNewVec3(0.0f, 1.0f, 0.0f);
    camera->right = VXNewVec3(1.0f, 0.0f, 0.0f);
    camera->forward = VXNewVec3(0.0f, 0.0f, 1.0f);

    i32 w, h;
    glfwGetWindowSize(window, &w, &h);
    glfwSetWindowUserPointer(window, camera);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    camera->view = VXLookAtMat4(camera->pos, VXAddVec3(camera->pos, camera->forward), camera->up);
    camera->proj = VXPerspectiveMat4(camera->fov, (f32)w / (f32)h, 0.1f, 2000.0f);

    return VX_OK;
}

void VXComputeCameraView(VXCamera* camera) {
    if (!camera) return;
    camera->view = VXLookAtMat4(camera->pos, VXAddVec3(camera->pos, camera->forward), camera->up);
}

void VXComputeCameraProjection(f32 aspect, f32 near, f32 far, VXCamera* camera) {
    if (!camera) return;
    camera->proj = VXPerspectiveMat4(camera->fov, aspect, near, far);
}

void VXComputeCameraVectors(VXCamera* camera) {
    if (!camera) return;

    camera->forward.x = cosf(camera->angle.y) * cosf(camera->angle.x);
    camera->forward.y = sinf(camera->angle.x);
    camera->forward.z = sinf(camera->angle.y) * cosf(camera->angle.x);

    camera->forward = VXNormVec3(camera->forward);
    camera->right = VXNormVec3(VXCrossVec3(camera->forward, VXNewVec3(0, 1, 0)));
    camera->up = VXNormVec3(VXCrossVec3(camera->right, camera->forward));
}

void VXYawCamera(f32 delta, VXCamera* camera) {
    if (!camera) return;
    camera->angle.y += delta;
}

void VXPitchCamera(f32 delta, VXCamera* camera) {
    if (!camera) return;
    f32 max = TO_RADIANS(89);
    camera->angle.x = CLAMP(camera->angle.x + delta, -max, max);
}

void VXMoveCameraLeft(VXCamera* camera) {
    if (!camera) return;
    camera->pos = VXSubVec3(camera->pos, VXScaleVec3(camera->right, camera->speed));
}

void VXMoveCameraRight(VXCamera* camera) {
    if (!camera) return;
    camera->pos = VXAddVec3(camera->pos, VXScaleVec3(camera->right, camera->speed));
}
void VXMoveCameraUp(VXCamera* camera) {
    if (!camera) return;
    camera->pos = VXAddVec3(camera->pos, VXScaleVec3(camera->up, camera->speed));
}

void VXMoveCameraDown(VXCamera* camera) {
    if (!camera) return;
    camera->pos = VXSubVec3(camera->pos, VXScaleVec3(camera->up, camera->speed));
}

void VXMoveCameraForward(VXCamera* camera) {
    if (!camera) return;
    camera->pos = VXAddVec3(camera->pos, VXScaleVec3(camera->forward, camera->speed));
}

void VXMoveCameraBackward(VXCamera* camera) {
    if (!camera) return;
    camera->pos = VXSubVec3(camera->pos, VXScaleVec3(camera->forward, camera->speed));
}
