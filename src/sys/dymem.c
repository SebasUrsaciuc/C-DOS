#include "sys/dymem.h"

#include "misc/mem.h"

mem_seg* fstseg;

void mem_init(uint32 addr, uint32 maxsize) {
    fstseg = (mem_seg*) addr;

    fstseg->prev = NULL;
    fstseg->next = NULL;
    fstseg->len = maxsize - sizeof(fstseg);
    fstseg->free = true;
}

void* mem_join(mem_seg* seg1, mem_seg* seg2) {
    mem_seg* tmp;

    if(seg2 < seg1) {
        tmp = seg1;
        seg1 = seg2;
        seg2 = tmp;
    }

    for(tmp = seg1->next; tmp <= seg2; tmp = tmp->next) {
        seg1->len += sizeof(tmp) + tmp->len;
        seg1->next = tmp->next;

        seg1->next->prev = seg1;
    }

    return seg1;
}

void mem_split(mem_seg* seg, uint32 seg1sz, mem_seg* (*ret)[2]) {
    (*ret)[0] = seg;

    if(seg->len < seg1sz + sizeof(mem_seg)) {
        (*ret)[1] = NULL;
        return;
    }

    mem_seg* seg2 = (mem_seg*) (((uint32) seg) + sizeof(mem_seg) + seg1sz);
    (*ret)[1] = seg2;

    seg2->prev = seg;
    seg2->next = seg->next;
    seg2->len = seg->len - (seg1sz + sizeof(mem_seg));
    seg2->free = seg->free;

    seg->next = seg2;
    seg->len = seg1sz;
}

void* mem_alloc(uint32 size) {
    size = mem_getAligned(size);

    mem_seg* seg = fstseg;

    while(true) {
        if(seg == NULL) {
            return NULL;
        } else if(seg->free && seg->len >= size + sizeof(mem_seg)) {
            if(seg->len != size) {
                mem_seg* segs[2];

                mem_split(seg, size, &segs);

                seg = segs[0];
                segs[1]->free = true;
            }

            seg->free = false;

            return seg + 1;
        } else {
            seg = seg->next;
        }
    }
}

void* mem_calloc(uint32 size) {
    void* ptr = mem_alloc(size);

    mem_set(ptr, 0, mem_getSize(ptr));

    return ptr;
}

void* mem_realloc(void* ptr, uint32 size) {
    void* nptr = mem_alloc(size);

    mem_copy(nptr, ptr, mem_getSize(ptr));

    mem_free(ptr);
    return nptr;
}

void mem_free(void* ptr) {
    mem_seg* seg = ((mem_seg*) ptr) - 1;

    if(seg->next != NULL && seg->next->free) {
        mem_join(seg, seg->next);
    }

    if(seg->prev != NULL && seg->prev->free) {
        mem_join(seg->prev, seg);
    }

    seg->free = true;
}