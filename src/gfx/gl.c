#include <include/VX/VX.h>
#include <stdint.h>
#include <stdio.h>


void VXClearColor(f32 r, f32 g, f32 b, f32 a) {
    glClearColor(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void VXClearDepth(f32 depth) {
    glClearDepth(depth);
    glClear(GL_DEPTH_BUFFER_BIT);
}

u32 VXNewVertexBuffer(u32 size, ptr data) {
    u32 vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

u32 VXNewVertexArray(u32 vbo, VXVertexLayout layout) {
    u32 vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    FOR_I(0, layout.count, 1) {
        VXVertexAttrib* a = &layout.attrs[i];
        glEnableVertexAttribArray(a->location);
        glVertexAttribIPointer(
            a->location,
            a->size,
            a->type,
            layout.stride,
            (ptr)(uintptr_t)a->offset
        );
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return vao;
}

u32 VXNewShader(const char* vertex, const char* fragment) {
    i32 pass;
    char info[512];

    u32 v = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v, 1, &vertex, NULL);
    glCompileShader(v);
    glGetShaderiv(v, GL_COMPILE_STATUS, &pass);
    if (!pass) {
        glGetShaderInfoLog(v, 512, NULL, info);
        printf("Vertex shader compilation failed: %s\n", info);
    }

    u32 f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f, 1, &fragment, NULL);
    glCompileShader(f);
    glGetShaderiv(f, GL_COMPILE_STATUS, &pass);
    if (!pass) {
        glGetShaderInfoLog(f, 512, NULL, info);
        printf("Fragment shader compilation failed: %s\n", info);
    }

    u32 p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);
    glGetProgramiv(p, GL_LINK_STATUS, &pass);
    if (!pass) {
        glGetProgramInfoLog(p, 512, NULL, info);
        printf("Shader program linking failed: %s\n", info);
    }

    glDeleteShader(v);
    glDeleteShader(f);
    return p;
}

void VXSetShaderUniform(char* name, ptr data, VXUniformType type, u32 shader) {
    i32 loc = glGetUniformLocation(shader, name);
    if (loc == -1) return;

    switch (type) {
        default: break;
        case VX_UNIFORM_INT: {
            glUniform1i(loc, *(i32*)data);
        } break;
        case VX_UNIFORM_FLOAT: {
            glUniform1f(loc, *(f32*)data);
        } break;
        case VX_UNIFORM_VEC2: {
            glUniform2fv(loc, 1, (f32*)data);
        } break;
        case VX_UNIFORM_VEC3: {
            glUniform3fv(loc, 1, (f32*)data);
        } break;
        case VX_UNIFORM_VEC4: {
            glUniform4fv(loc, 1, (f32*)data);
        } break;
        case VX_UNIFORM_MAT4: {
            glUniformMatrix4fv(loc, 1, GL_TRUE, (f32*)data);    // transpose on send
        } break;
    }
}
