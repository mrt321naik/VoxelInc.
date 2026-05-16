#include <include/VX/VX.h>


static VXVertexLayout VXVoxelLayout = {
    .count = 3,
    .stride = 5,
    .attrs = (VXVertexAttrib[]) {
        {.location = 0, .size = 3, .type = GL_UNSIGNED_BYTE, .normalized = GL_FALSE, .offset = 0},  // pos
        {.location = 1, .size = 1, .type = GL_UNSIGNED_BYTE, .normalized = GL_FALSE, .offset = 3},  // voxel
        {.location = 2, .size = 1, .type = GL_UNSIGNED_BYTE, .normalized = GL_FALSE, .offset = 4}   // face
    }
};

u8 VXVoxelAt(VXVec3 pos, VXChunk* chunk) {
    if (!chunk) return 0;
    i32 x = (i32)pos.x;
    i32 y = (i32)pos.y;
    i32 z = (i32)pos.z;
    u32 i = x + 32 * z + 1024 * y;
    if (0 <= x && x < 32
    &&  0 <= y && y < 32
    &&  0 <= z && z < 32) {
        return chunk->data[i];
    } return 0;
}

// for now there are:
// 5 attribs per vertex
// 18 vertices per face
// 3 max faces per voxel
// u8 attribs: x, y, z, type, face
void VXBuildChunk(VXChunk* chunk, VXArena* arena) {
    if (!arena || arena->used == arena->size || !chunk) return;

    u8* data = VXGetArena(VX_CHUNK_VOLUME * 18 * 5, arena);
    if (!data) return;

    // batshit implementation of per-voxel face culling
    u32 index = 0;
    FOR(u32, x, 0, 32, 1) {
        FOR(u32, y, 0, 32, 1) {
            FOR(u32, z, 0, 32, 1) {
                u8 voxel = VXVoxelAt(VXNewVec3(x, y, z), chunk);
                if (!voxel) continue;

                // top face
                if (!VXVoxelAt(VXNewVec3(x, y + 1, z), chunk)) {
                    u8 v0[] = {x, y + 1, z, voxel, 0};
                    u8 v1[] = {x + 1, y + 1, z, voxel, 0};
                    u8 v2[] = {x + 1, y + 1, z + 1, voxel, 0};
                    u8 v3[] = {x, y + 1, z + 1, voxel, 0};

                    u8* face[] = {v0, v3, v2, v0, v2, v1};
                    FOR_I(0, 6, 1) {
                        FOR_J(0, 5, 1) {
                            data[index++] = face[i][j];
                        }
                    }
                }
                // bottom face
                if (!VXVoxelAt(VXNewVec3(x, y - 1, z), chunk)) {
                    u8 v0[] = {x, y, z, voxel, 1};
                    u8 v1[] = {x + 1, y, z, voxel, 1};
                    u8 v2[] = {x + 1, y, z + 1, voxel, 1};
                    u8 v3[] = {x, y, z + 1, voxel, 1};

                    u8* face[] = {v0, v2, v3, v0, v1, v2};
                    FOR_I(0, 6, 1) {
                        FOR_J(0, 5, 1) {
                            data[index++] = face[i][j];
                        }
                    }
                }
                // right face
                if (!VXVoxelAt(VXNewVec3(x + 1, y, z), chunk)) {
                    u8 v0[] = {x + 1, y, z, voxel, 2};
                    u8 v1[] = {x + 1, y + 1, z, voxel, 2};
                    u8 v2[] = {x + 1, y + 1, z + 1, voxel, 2};
                    u8 v3[] = {x + 1, y, z + 1, voxel, 2};

                    u8* face[] = {v0, v1, v2, v0, v2, v3};
                    FOR_I(0, 6, 1) {
                        FOR_J(0, 5, 1) {
                            data[index++] = face[i][j];
                        }
                    }
                }
                // left face
                if (!VXVoxelAt(VXNewVec3(x - 1, y, z), chunk)) {
                    u8 v0[] = {x, y, z, voxel, 3};
                    u8 v1[] = {x, y + 1, z, voxel, 3};
                    u8 v2[] = {x, y + 1, z + 1, voxel, 3};
                    u8 v3[] = {x, y, z + 1, voxel, 3};

                    u8* face[] = {v0, v2, v1, v0, v3, v2};
                    FOR_I(0, 6, 1) {
                        FOR_J(0, 5, 1) {
                            data[index++] = face[i][j];
                        }
                    }
                }
                // back face
                if (!VXVoxelAt(VXNewVec3(x, y, z - 1), chunk)) {
                    u8 v0[] = {x, y, z, voxel, 4};
                    u8 v1[] = {x, y + 1, z, voxel, 4};
                    u8 v2[] = {x + 1, y + 1, z, voxel, 4};
                    u8 v3[] = {x + 1, y, z, voxel, 4};

                    u8* face[] = {v0, v1, v2, v0, v2, v3};
                    FOR_I(0, 6, 1) {
                        FOR_J(0, 5, 1) {
                            data[index++] = face[i][j];
                        }
                    }
                }
                // front face
                if (!VXVoxelAt(VXNewVec3(x, y, z + 1), chunk)) {
                    u8 v0[] = {x, y, z + 1, voxel, 5};
                    u8 v1[] = {x, y + 1, z + 1, voxel, 5};
                    u8 v2[] = {x + 1, y + 1, z + 1, voxel, 5};
                    u8 v3[] = {x + 1, y, z + 1, voxel, 5};

                    u8* face[] = {v0, v2, v1, v0, v3, v2};
                    FOR_I(0, 6, 1) {
                        FOR_J(0, 5, 1) {
                            data[index++] = face[i][j];
                        }
                    }
                }
            }
        }
    } VXResetArena(arena);

    chunk->mesh.verts = VXAlloc(index);
    if (!chunk->mesh.verts) return;
    if (VXWriteMem(index, data, chunk->mesh.verts) == VX_ERROR) {
        VXFree(chunk->mesh.verts);
        return;
    }

    chunk->mesh.size = index;
    chunk->mesh.count = index / 5;
    chunk->mesh.matrix = VXIdentityMat4();

    chunk->mesh.vbo = VXNewVertexBuffer(index, chunk->mesh.verts);
    chunk->mesh.vao = VXNewVertexArray(chunk->mesh.vbo, VXVoxelLayout);
    if (!chunk->mesh.vbo || !chunk->mesh.vao) {
        VXFree(chunk->mesh.verts);
        return;
    }
}
