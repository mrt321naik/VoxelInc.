#include <include/VX/VX.h>
#include <stdlib.h>


VXResult VXNewArena(u64 size, VXArena* arena) {
    if (!size || !arena) return VX_ERROR;

    arena->data = VXAlloc(size);
    if (!arena->data) return VX_ERROR;

    arena->size = size;
    arena->used = 0;

    return VX_OK;
}

ptr VXGetArena(u64 size, VXArena* arena) {
    if (!size || !arena
    ||  arena->used + size > arena->size) return NULL;

    ptr result = (ptr)((u8*)arena->data + arena->used);
    arena->used += size;
    return result;
}

VXResult VXReallocArena(u64 size, VXArena* arena) {
    if (!arena) return VX_ERROR;

    ptr n = VXRealloc(size, arena->size, arena->data);
    if (!n) return VX_ERROR;
    arena->size = size;
    arena->data = n;

    return VX_OK;
}

VXResult VXResetArena(VXArena* arena) {
    if (!arena) return VX_ERROR;
    arena->used = 0;
    return VX_OK;
}

VXResult VXDelArena(VXArena* arena) {
    if (!arena) return VX_ERROR;

    if (arena->data) VXFree(arena->data);
    arena->data = NULL;
    arena->size = 0;
    arena->used = 0;

    return VX_OK;
}
