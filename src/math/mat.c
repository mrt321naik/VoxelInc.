#include <include/VX/math.h>
#include <stdio.h>
#include <math.h>

VXMat4 VXNewMat4(void) {
    return (VXMat4){0};
}

VXMat4 VXIdentityMat4(void) {
    return (VXMat4){
        .m[0] = {1.0f, 0.0f, 0.0f, 0.0f},
        .m[1] = {0.0f, 1.0f, 0.0f, 0.0f},
        .m[2] = {0.0f, 0.0f, 1.0f, 0.0f},
        .m[3] = {0.0f, 0.0f, 0.0f, 1.0f},
    };
}

VXMat4 VXScalingMat4(f32 sx, f32 sy, f32 sz) {
    return (VXMat4){
        .m[0] = {sx, 0.0f, 0.0f, 0.0f},
        .m[1] = {0.0f, sy, 0.0f, 0.0f},
        .m[2] = {0.0f, 0.0f, sz, 0.0f},
        .m[3] = {0.0f, 0.0f, 0.0f, 1.0f},
    };
}

VXMat4 VXTranslationMat4(f32 tx, f32 ty, f32 tz) {
    return (VXMat4){
        .m[0] = {1.0f, 0.0f, 0.0f, tx},
        .m[1] = {0.0f, 1.0f, 0.0f, ty},
        .m[2] = {0.0f, 0.0f, 1.0f, tz},
        .m[3] = {0.0f, 0.0f, 0.0f, 1.0f},
    };
}

VXMat4 VXRotationXMat4(f32 angle) {
    f32 c = cos(angle);
    f32 s = sin(angle);
    return (VXMat4){
        .m[0] = {1.0f, 0.0f, 0.0f, 0.0f},
        .m[1] = {0.0f, c, -s, 0.0f},
        .m[2] = {0.0f, s, c, 0.0f},
        .m[3] = {0.0f, 0.0f, 0.0f, 1.0f},
    };
}

VXMat4 VXRotationYMat4(f32 angle) {
    f32 c = cos(angle);
    f32 s = sin(angle);
    return (VXMat4){
        .m[0] = {c, 0.0f, s, 0.0f},
        .m[1] = {0.0f, 1.0f, 0.0f, 0.0f},
        .m[2] = {-s, 0.0f, c, 0.0f},
        .m[3] = {0.0f, 0.0f, 0.0f, 1.0f},
    };
}

VXMat4 VXRotationZMat4(f32 angle) {
    f32 c = cos(angle);
    f32 s = sin(angle);
    return (VXMat4){
        .m[0] = {c, -s, 0.0f, 0.0f},
        .m[1] = {s, c, 0.0f, 0.0f},
        .m[2] = {0.0f, 0.0f, 1.0f, 0.0f},
        .m[3] = {0.0f, 0.0f, 0.0f, 1.0f},
    };
}

VXMat4 VXTransposeMat4(VXMat4 m) {
    return (VXMat4){
        .m[0] = {m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0]},
        .m[1] = {m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1]},
        .m[2] = {m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2]},
        .m[3] = {m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]},
    };
}

VXMat4 VXAddMat4(VXMat4 a, VXMat4 b) {
    VXMat4 r = VXNewMat4();
    FOR_I(0, 4, 1) {
        FOR_J(0, 4, 1) {
            r.m[i][j] = a.m[i][j] + b.m[i][j];
        }
    } return r;
}

VXMat4 VXSubMat4(VXMat4 a, VXMat4 b) {
    VXMat4 r = VXNewMat4();
    FOR_I(0, 4, 1) {
        FOR_J(0, 4, 1) {
            r.m[i][j] = a.m[i][j] - b.m[i][j];
        }
    } return r;
}

VXMat4 VXScaleMat4(VXMat4 m, f32 s) {
    VXMat4 r = VXNewMat4();
    FOR_I(0, 4, 1) {
        FOR_J(0, 4, 1) {
            r.m[i][j] = m.m[i][j] * s;
        }
    } return r;
}

VXMat4 VXMulMat4(VXMat4 a, VXMat4 b) {
    VXMat4 r = VXNewMat4();
    FOR_I(0, 4, 1) {
        FOR_J(0, 4, 1) {
            f32 s = 0;
            FOR_K(0, 4, 1) {
                s += a.m[i][k] * b.m[k][j];
            } r.m[i][j] = s;
        }
    } return r;
}

VXVec3 VXMulMat4Vec3(VXMat4 m, VXVec3 v) {
    f32 x = v.x, y = v.y, z = v.z;
    f32 rx = m.m[0][0]*x + m.m[0][1]*y + m.m[0][2]*z + m.m[0][3]*1.0f;
    f32 ry = m.m[1][0]*x + m.m[1][1]*y + m.m[1][2]*z + m.m[1][3]*1.0f;
    f32 rz = m.m[2][0]*x + m.m[2][1]*y + m.m[2][2]*z + m.m[2][3]*1.0f;
    return (VXVec3){ rx, ry, rz };
}

VXVec4 VXMulMat4Vec4(VXMat4 m, VXVec4 v) {
    return (VXVec4){
        .x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w,
        .y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w,
        .z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w,
        .w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w
    };
}

VXMat4 VXLookAtMat4(VXVec3 eye, VXVec3 target, VXVec3 up) {
    VXVec3 z = VXNormVec3(VXSubVec3(eye, target));
    VXVec3 x = VXNormVec3(VXCrossVec3(VXNormVec3(up), z));
    VXVec3 y = VXNormVec3(VXCrossVec3(z, x));

    VXMat4 t = VXIdentityMat4();
    t.m[0][3] = -eye.x;
    t.m[1][3] = -eye.y;
    t.m[2][3] = -eye.z;

    VXMat4 r = VXIdentityMat4();
    r.m[0][0] = x.x; r.m[0][1] = x.y; r.m[0][2] = x.z;
    r.m[1][0] = y.x; r.m[1][1] = y.y; r.m[1][2] = y.z;
    r.m[2][0] = z.x; r.m[2][1] = z.y; r.m[2][2] = z.z;

    return VXMulMat4(r, t);
}

VXMat4 VXPerspectiveMat4(f32 fov, f32 aspect, f32 near, f32 far) {
    fov *= 3.14159 / 180.0f;
    f32 d = 1.0f / (near - far);
    f32 f = 1.0f / tanf(fov * 0.5f);

    return (VXMat4){
        .m[0] = { f / aspect, 0.0f, 0.0f, 0.0f },
        .m[1] = { 0.0f, f, 0.0f, 0.0f },
        .m[2] = { 0.0f, 0.0f, (far + near) * d, (2.0f * far * near) * d },
        .m[3] = { 0.0f, 0.0f, -1.0f, 0.0f }
    };
}

void VXPrintMat4(char* tag, VXMat4 m) {
    printf("%s:\n", tag);
    for (int i = 0; i < 4; i++) {
        printf("\t[ %.4f  %.4f  %.4f  %.4f ]\n",
            m.m[i][0],
            m.m[i][1],
            m.m[i][2],
            m.m[i][3]
        );
    }
}
