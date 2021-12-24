#pragma once

#include "def.h"

typedef struct mem_seg mem_seg;

struct mem_seg {
    uint32 len;
    mem_seg* prev;
    mem_seg* next;
    bool free;
} PACKED;

#define MEM_HEAP_ALIGN 4

/* Get the size of an allocated memory segment. */
#define mem_getAligned(sz) (sz + (MEM_HEAP_ALIGN - (sz % MEM_HEAP_ALIGN)) % MEM_HEAP_ALIGN)

/* Get the size of an allocated memory segment. */
#define mem_getSize(ptr) ((((mem_seg*) ptr) - 1)->len)

/* Initializes the heap. */
void mem_init(uint32 addr, uint32 maxsize);

/* Merges two memory segments.
   All the segments between the boundaries will be joined! */
void* mem_join(mem_seg* seg1, mem_seg* seg2);

/* Splits a memory segment into two parts. */
void mem_split(mem_seg* seg, uint32 seg1sz, mem_seg* (*ret)[2]);

/* Allocates a segment of memory. */
void* mem_alloc(uint32 size);

/* Allocates a segment of memory and clears it. */
void* mem_calloc(uint32 size);

/* Reallocates a segment of memory, resizing it. */
void* mem_realloc(void* ptr, uint32 size);

/* Frees an allocated memory segment. */
void mem_free(void* ptr);