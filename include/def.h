#pragma once

#define null ((void*) 0)

#define attr(...) __attribute__((__VA_ARGS__))

typedef __INT8_TYPE__ int8;
typedef __UINT8_TYPE__ uint8;
typedef __INT16_TYPE__ int16;
typedef __UINT16_TYPE__ uint16;
typedef __INT32_TYPE__ int32;
typedef __UINT32_TYPE__ uint32;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

typedef uint8 byte;
typedef uint16 word;
typedef uint32 dword;

typedef enum { false, true } bool;