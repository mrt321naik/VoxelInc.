#pragma once

#include <include/VX/gfx.h>
#include <include/VX/mem.h>
#include <include/VX/math.h>

/*
 * Voxel vertex data format: x,y,z,u,v,t (f32, f32, f32, f32, f32, u32)
 * Chunk meshing algorithm:
 * Face Culling (greedy meshing later)
 *  for voxel in chunk:
 *      if solid:
 *          for adjacent voxels:
 *              if not solid:
 *                  emit face
 */

typedef struct VXChunk {
    u8 data[VX_CHUNK_VOLUME];   // chunk data stored in a linear buffer (i = x * w + (y + h * z))
    VXMesh mesh;
    u8 mask;                    // bitmask for chunk state
} VXChunk;

typedef struct VXScene {
    VXChunk* chunks;    // chunks are stored in a linear buffer (i = x * w + (y + h * z))
    VXVec3 dimensions;  // dimensions of the scene in chunks
    u32 nchunks;
} VXScene;
