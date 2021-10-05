#include "dymem.h"

#include "mem.h"

memseg* fstseg;

void initheap(uint32 addr, uint32 size) {
    fstseg = (memseg*) addr;

    fstseg->prev = null;
    fstseg->next = null;
    fstseg->len = size - sizeof(fstseg);
    fstseg->free = true;
}

void* mjoin(memseg* seg1, memseg* seg2) {
    memseg* tmp;

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

void msplit(memseg* seg, uint32 seg1sz, memseg* (*ret)[2]) {
    (*ret)[0] = seg;

    if(seg->len < seg1sz + sizeof(memseg)) {
        (*ret)[1] = null;
        return;
    }

    memseg* seg2 = (memseg*) (((uint32) seg) + sizeof(memseg) + seg1sz);
    (*ret)[1] = seg2;

    seg2->prev = seg;
    seg2->next = seg->next;
    seg2->len = seg->len - (seg1sz + sizeof(memseg));
    seg2->free = seg->free;

    seg->next = seg2;
    seg->len = seg1sz;
}

void* malloc(uint32 size) {
    size = malnsz(size);

    memseg* seg = fstseg;

    while(true) {
        if(seg == null) {
            return null;
        } else if(seg->free && seg->len >= size + sizeof(memseg)) {
            if(seg->len != size) {
                memseg* segs[2];

                msplit(seg, size, &segs);

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

void* calloc(uint32 size) {
    void* ptr = malloc(size);

    memset(ptr, 0, msize(ptr));

    return ptr;
}

void* realloc(void* ptr, uint32 size) {
    void* nptr = malloc(size);

    memcpy(nptr, ptr, msize(ptr));

    mfree(ptr);
    return nptr;
}

void mfree(void* ptr) {
    memseg* seg = ((memseg*) ptr) - 1;

    if(seg->next != null && seg->next->free) {
        mjoin(seg, seg->next);
    }

    if(seg->prev != null && seg->prev->free) {
        mjoin(seg->prev, seg);
    }

    seg->free = true;
}

uint32 msize(void* ptr) {
    return (((memseg*) ptr) - 1)->len;
}