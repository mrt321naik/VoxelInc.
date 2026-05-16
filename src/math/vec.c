#include <include/VX/math.h>
#include <stdio.h>
#include <math.h>

VXVec4 VXNewVec4(float x, float y, float z, float w) {
    return (VXVec4){x, y, z, w};
}

VXVec4 VXScaleVec4(VXVec4 v, float s) {
    return (VXVec4){v.x * s, v.y * s, v.z * s, v.w * s};
}

VXVec4 VXDotVec4(VXVec4 a, VXVec4 b) {
    return (VXVec4){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

VXVec4 VXDivVec4(VXVec4 a, VXVec4 b) {
    return (VXVec4){a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}

VXVec4 VXSubVec4(VXVec4 a, VXVec4 b) {
    return (VXVec4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

VXVec4 VXAddVec4(VXVec4 a, VXVec4 b) {
    return (VXVec4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

VXVec4 VXNormVec4(VXVec4 v) {
    f32 m = VXMagVec4(v);
    return (VXVec4){v.x / m, v.y / m, v.z / m, v.w / m};
}

f32 VXMagVec4(VXVec4 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

void VXPrintVec4(char* tag, VXVec4 v) {
    printf("%s:\tVec4( %.4f, %.4f, %.4f, %.4f )\n", tag, v.x, v.y, v.z, v.w);
}


VXVec3 VXNewVec3(float x, float y, float z) {
    return (VXVec3){x, y, z};
}

VXVec3 VXCrossVec3(VXVec3 a, VXVec3 b) {
    return (VXVec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

VXVec3 VXDotVec3(VXVec3 a, VXVec3 b) {
    return (VXVec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

VXVec3 VXScaleVec3(VXVec3 v, float s) {
    return (VXVec3){v.x * s, v.y * s, v.z * s};
}

VXVec3 VXDivVec3(VXVec3 a, VXVec3 b) {
    return (VXVec3){a.x / b.x, a.y / b.y, a.z / b.z};
}

VXVec3 VXSubVec3(VXVec3 a, VXVec3 b) {
    return (VXVec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

VXVec3 VXAddVec3(VXVec3 a, VXVec3 b) {
    return (VXVec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

VXVec3 VXNormVec3(VXVec3 v) {
    f32 m = VXMagVec3(v);
    return (VXVec3){v.x / m, v.y / m, v.z / m};
}

f32 VXMagVec3(VXVec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

void VXPrintVec3(char* tag, VXVec3 v) {
    printf("%s:\tVec3( %.4f, %.4f, %.4f )\n", tag, v.x, v.y, v.z);
}
