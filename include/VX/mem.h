#pragma once

#include <include/VX/def.h>

typedef struct VXArena {
    void* data;
    u64 size;
    u64 used;
} VXArena;

ptr VXAlloc(u64 size);
VXResult VXFree(ptr p);
ptr VXAlloca(u64 size, u64 align);
ptr VXRealloc(u64 nsize, u64 osize, ptr p);
VXResult VXSetMem(u64 size, u8 value, ptr p);
VXResult VXReadMem(u64 size, ptr src, ptr dst);
VXResult VXWriteMem(u64 size, ptr src, ptr dst);
ptr VXRealloca(u64 nsize, u64 osize, u64 align, ptr p);

VXResult VXNewArena(u64 size, VXArena* arena);
ptr VXGetArena(u64 size, VXArena* arena);
VXResult VXResetArena(VXArena* arena);
VXResult VXDelArena(VXArena* arena);
