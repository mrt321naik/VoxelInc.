#include <include/VX/VX.h>
#include <stdlib.h>
#include <string.h>

ptr VXAlloc(u64 size) {
    return VXAlloca(size, VX_ALIGNMENT);
}

ptr VXAlloca(u64 size, u64 align) {
    if (!size || !align || (align & (align - 1))) return NULL;

    u64 p = (u64)malloc(sizeof(u64) + (size + (align - 1)));
    if (!p) return NULL;

    u64 a = (u64)(((u8*)p + sizeof(u64)) + (align - 1)) & ~(align - 1);
    ((u64*)a)[-1] = p;

    VXSetMem(size, 0, (ptr)a);
    return (ptr)a;
}

ptr VXRealloc(u64 nsize, u64 osize, ptr p) {
    return VXRealloca(nsize, osize, VX_ALIGNMENT, p);
}

ptr VXRealloca(u64 nsize, u64 osize, u64 align, ptr p) {
    if (!p || !nsize || !align || (align & (align - 1))) return p;

    ptr o = (ptr)((u64*)p)[-1];

    u64 n = (u64)realloc(o, sizeof(u64) + (nsize + (align - 1)));
    if (!n) return p;

    u64 a = (u64)(((u8*)n + sizeof(u64)) + (align - 1)) & ~(align - 1);
    ((u64*)a)[-1] = n;

    if (nsize > osize) {
        VXSetMem(nsize - osize, 0, (ptr)((u8*)a + osize));
    } return (ptr)a;
}

VXResult VXFree(ptr p) {
    if (!p) return VX_ERROR;
    free((ptr)((u64*)p)[-1]);
    return VX_OK;
}

VXResult VXSetMem(u64 size, u8 value, ptr p) {
    if (!size || !p) return VX_ERROR;
    memset(p, value, size);
    return VX_OK;
}

VXResult VXReadMem(u64 size, ptr src, ptr dst) {
    if (!size || !src || !dst) return VX_ERROR;
    memcpy(dst, src, size);
    return VX_OK;
}

VXResult VXWriteMem(u64 size, ptr src, ptr dst) {
    if (!size || !src || !dst) return VX_ERROR;
    memcpy(dst, src, size);
    return VX_OK;
}
