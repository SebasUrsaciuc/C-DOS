#pragma once

#include "def.h"

#define HEAP_ALIGN 4

#define malnsz(sz) (sz + (HEAP_ALIGN - (sz % HEAP_ALIGN)) % HEAP_ALIGN)

typedef struct memseg memseg;
struct memseg {
    uint32 len;
    memseg* prev;
    memseg* next;
    bool free;
} attr(packed);

/* Initializes the heap. */
void initheap(uint32 addr, uint32 maxsize);

/* Merges two memory segments.
   All the segments between the boundaries will be joined! */
void* mjoin(memseg* seg1, memseg* seg2);

/* Splits a memory segment into two parts. */
void msplit(memseg* seg, uint32 seg1sz, memseg* (*ret)[2]);

/* Allocates a segment of memory. */
void* malloc(uint32 size);

/* Allocates a segment of memory and clears it. */
void* calloc(uint32 size);

/* Reallocates a segment of memory, resizing it. */
void* realloc(void* ptr, uint32 size);

/* Frees an allocated memory segment. */
void mfree(void* ptr);

/* Get the size of an allocated memory segment. */
uint32 msize(void* ptr);