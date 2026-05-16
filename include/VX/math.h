#pragma once

#include <include/VX/def.h>

typedef struct VXVec3 {
    float x, y, z;
} VXVec3;

typedef struct {
    f32 x, y, z, w;
} VXVec4;

typedef struct VXMat4 {
    float m[4][4];
} VXMat4;

#define TO_RADIANS(deg) ((deg) * M_PI / 180.0f)
#define TO_DEGREES(rad) ((rad) * 180.0f / M_PI)

VXVec4 VXNewVec4(float x, float y, float z, float w);
void VXPrintVec4(char* tag, VXVec4 m);
VXVec4 VXScaleVec4(VXVec4 v, float s);
VXVec4 VXDotVec4(VXVec4 a, VXVec4 b);
VXVec4 VXDivVec4(VXVec4 a, VXVec4 b);
VXVec4 VXSubVec4(VXVec4 a, VXVec4 b);
VXVec4 VXAddVec4(VXVec4 a, VXVec4 b);
VXVec4 VXNormVec4(VXVec4 v);
f32 VXMagVec4(VXVec4 v);

VXVec3 VXNewVec3(float x, float y, float z);
VXVec3 VXCrossVec3(VXVec3 a, VXVec3 b);
VXVec3 VXScaleVec3(VXVec3 v, float s);
void VXPrintVec3(char* tag, VXVec3 m);
VXVec3 VXDotVec3(VXVec3 a, VXVec3 b);
VXVec3 VXDivVec3(VXVec3 a, VXVec3 b);
VXVec3 VXSubVec3(VXVec3 a, VXVec3 b);
VXVec3 VXAddVec3(VXVec3 a, VXVec3 b);
VXVec3 VXNormVec3(VXVec3 v);
f32 VXMagVec3(VXVec3 v);

VXMat4 VXNewMat4(void);
VXMat4 VXIdentityMat4(void);
VXMat4 VXTransposeMat4(VXMat4 m);
VXMat4 VXRotationXMat4(f32 angle);
VXMat4 VXRotationYMat4(f32 angle);
VXMat4 VXRotationZMat4(f32 angle);
VXMat4 VXScaleMat4(VXMat4 m, f32 s);
VXMat4 VXAddMat4(VXMat4 a, VXMat4 b);
VXMat4 VXSubMat4(VXMat4 a, VXMat4 b);
VXMat4 VXMulMat4(VXMat4 a, VXMat4 b);
void VXPrintMat4(char* tag, VXMat4 m);
VXVec3 VXMulMat4Vec3(VXMat4 m, VXVec3 v);
VXMat4 VXScalingMat4(f32 sx, f32 sy, f32 sz);
VXMat4 VXTranslationMat4(f32 tx, f32 ty, f32 tz);
VXMat4 VXLookAtMat4(VXVec3 eye, VXVec3 target, VXVec3 up);
VXMat4 VXPerspectiveMat4(f32 fov, f32 aspect, f32 near, f32 far);
