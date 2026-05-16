#pragma once

#include <include/GLEW/glew.h>
#include <include/GLFW/glfw3.h>
#include <include/VX/math.h>

typedef struct VXInputCallback {
    void (*func)(GLFWwindow* window);
    i32 key;
} VXInputCallback;

typedef struct VXCamera {
    VXVec3 angle;   // pitch,yaw,roll
    VXVec3 pos;

    VXVec3 forward;
    VXVec3 right;
    VXVec3 up;

    VXMat4 view;
    VXMat4 proj;

    f32 speed;
    f32 fov;
} VXCamera;

typedef enum VXUniformType {
    VX_UNIFORM_INT,
    VX_UNIFORM_VEC2,
    VX_UNIFORM_VEC3,
    VX_UNIFORM_VEC4,
    VX_UNIFORM_MAT4,
    VX_UNIFORM_FLOAT,
} VXUniformType;

typedef struct {
    u32 size;
    u32 type;
    i32 offset;
    u32 location;
    u32 normalized;
} VXVertexAttrib;

typedef struct {
    VXVertexAttrib* attrs;
    u32 stride;
    u32 count;
} VXVertexLayout;

typedef struct VXMesh {
    VXMat4 matrix;
    u8* verts;
    u32 count;
    u32 size;
    u32 vao;
    u32 vbo;
} VXMesh;

GLFWwindow* VXNewWindow(u32 width, u32 height, char* title);
VXResult VXDelWindow(GLFWwindow* window);

u32 VXButtonPressed(i32 button, GLFWwindow* window);
u32 VXButtonHeld(i32 button, GLFWwindow* window);
u32 VXKeyPressed(i32 key, GLFWwindow* window);
u32 VXKeyHeld(i32 key, GLFWwindow* window);

VXResult VXNewInputCallback(void (*func)(GLFWwindow* window), i32 key);
void VXRunInputCallbacks(GLFWwindow* window);
VXResult VXDelInputCallback(i32 key);

u32 VXNewVertexBuffer(u32 size, ptr data);
u32 VXNewVertexArray(u32 vbo, VXVertexLayout layout);
u32 VXNewShader(const char* vertex, const char* fragment);
void VXSetShaderUniform(char* name, ptr data, VXUniformType type, u32 shader);
