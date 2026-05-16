#include <include/VX/VX.h>


VXResult VXNewScene(VXVec3 dimensions, VXScene* scene) {
    if (!dimensions.x || !dimensions.y || !dimensions.z || !scene) return VX_ERROR;

    scene->chunks = VXAlloc(dimensions.x * dimensions.y * dimensions.z * sizeof(VXChunk));
    if (!scene->chunks) return VX_ERROR;

    scene->nchunks = dimensions.x * dimensions.y * dimensions.z;
    scene->dimensions = dimensions;

    return VX_OK;
}

u32 VXGetChunkIndex(VXVec3 pos, VXScene* scene) {
    return pos.x + scene->dimensions.x * pos.y + scene->dimensions.x * scene->dimensions.y * pos.z;
}

VXChunk* VXGetChunk(VXVec3 pos, VXScene* scene) {
    if (pos.x >= scene->dimensions.x
    ||  pos.y >= scene->dimensions.y
    ||  pos.z >= scene->dimensions.z) {
        return NULL;
    }

    u32 i = VXGetChunkIndex(pos, scene);
    if (i >= scene->nchunks) return NULL;
    return &scene->chunks[i];
}

VXResult VXSetChunk(VXVec3 pos, VXChunk* chunk, VXScene* scene) {
    u32 i = VXGetChunkIndex(pos, scene);
    if (i >= scene->nchunks) return VX_ERROR;
    scene->chunks[i] = *chunk;
    return VX_OK;
}

VXResult VXResetChunk(VXVec3 pos, VXScene* scene) {
    u32 i = VXGetChunkIndex(pos, scene);
    if (i >= scene->nchunks) return VX_ERROR;
    return VXSetMem(sizeof(scene->chunks[i].data), 0, scene->chunks[i].data);
}

VXResult VXDelScene(VXScene* scene) {
    if (!scene) return VX_ERROR;

    if (scene->chunks) {
        FOR(u32, i, 0, scene->nchunks, 1) {
            VXFree(scene->chunks[i].mesh.verts);
        } VXFree(scene->chunks);
    }

    scene->chunks = NULL;
    scene->nchunks = 0;

    return VX_OK;
}
