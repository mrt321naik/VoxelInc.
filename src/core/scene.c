#include <include/VX/VX.h>


VXResult VXNewScene(VXVec3 dimensions, VXScene* scene) {
    if (!dimensions.x || !dimensions.y || !dimensions.z || !scene) return VX_ERROR;

    scene->chunks = VXAlloc(dimensions.x * dimensions.y * dimensions.z * sizeof(VXChunk));
    if (!scene->chunks) return VX_ERROR;

    scene->nchunks = dimensions.x * dimensions.y * dimensions.z;
    scene->dimensions = dimensions;

    return VX_OK;
}

VXChunk* VXGetChunk(VXVec3 pos, VXScene* scene) {
    u32 i = pos.x * scene->dimensions.x + (pos.y + scene->dimensions.y * pos.z);
    if (i >= scene->nchunks) return NULL;
    return &scene->chunks[i];
}

VXResult VXSetChunk(VXVec3 pos, VXChunk* chunk, VXScene* scene) {
    u32 i = pos.x * scene->dimensions.x + (pos.y + scene->dimensions.y * pos.z);
    if (i >= scene->nchunks) return VX_ERROR;
    scene->chunks[i] = *chunk;
    return VX_OK;
}

VXResult VXResetChunk(VXVec3 pos, VXScene* scene) {
    u32 i = pos.x * scene->nchunks + (pos.y + pos.z * scene->nchunks);
    if (i >= scene->nchunks) return VX_ERROR;
    return VXSetMem(sizeof(scene->chunks[i].data), 0, scene->chunks[i].data);
}

VXResult VXDelScene(VXScene* scene) {
    if (!scene) return VX_ERROR;

    if (scene->chunks) VXFree(scene->chunks);
    scene->chunks = NULL;
    scene->nchunks = 0;

    return VX_OK;
}
