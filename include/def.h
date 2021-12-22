#pragma once

#define NULL ((void*) 0)

#define attr(...) __attribute__((__VA_ARGS__))
#define sect(s) __section__("." #s)
#define asmv(...) asm volatile(__VA_ARGS__)

#define PACKED attr(packed)

typedef __INT8_TYPE__ i8, int8, int8_t;
typedef __UINT8_TYPE__ u8, uint8, uint8_t, byte;
typedef __INT16_TYPE__ i16, int16, int16_t;
typedef __UINT16_TYPE__ u16, uint16, uint16_t, word;
typedef __INT32_TYPE__ i32, int32, int32_t;
typedef __UINT32_TYPE__ u32, uint32, uint32_t, dword;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

typedef enum { false, true } bool;