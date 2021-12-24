#include "misc/mem.h"

void mem_set(void* ptr, uint8 val, uint32 num) {
    uint8* tptr = (uint8*) ptr;

    for(uint32 i = 0; i < num; i++) {
        tptr[i] = val;
    }
}

void mem_copy(void* dest, void* src, uint32 num) {
    uint8* tdest = (uint8*) dest;
    uint8* tsrc = (uint8*) src;

    for(uint32 i = 0; i < num; i++) {
        tdest[i] = tsrc[i];
    }
}