#pragma once

typedef signed char         i8;
typedef signed short        i16;
typedef signed int          i32;
typedef signed long long    i64;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef float               f32;
typedef double              f64;

typedef void*               ptr;

typedef enum VXResult {
    VX_ERROR,
    VX_WARN,
    VX_OK
} VXResult;

#define VX_ALIGNMENT 8
#define VX_CHUNK_VOLUME 32*32*32

#define FLIP_BIT(v, b)  ((v) ^ (1<<(b)))
#define SET_BITS(v, b)  ((v) | (1<<(b)))
#define GET_BITS(v, b)  ((v) & (1<<(b)))
#define REM_BITS(v, b)  ((v) & ~(1<<(b)))

#define FOR_I(start, stop, step) for (u32 i = start; i < stop; i += step)
#define FOR_J(start, stop, step) for (u32 j = start; j < stop; j += step)
#define FOR_K(start, stop, step) for (u32 k = start; k < stop; k += step)
#define FOR_L(start, stop, step) for (u32 l = start; l < stop; l += step)
#define FOR(type, iter, start, stop, step) for (type iter = start; iter < stop; iter += step)
