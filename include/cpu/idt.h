#pragma once

#include "cpu/int.h"

typedef struct PACKED {
    uint16 botOff;
    uint16 gdtCodeSeg;
    uint8 res;
    uint8 attr;
    uint16 topOff;
} idt_entry, idt_gate;

typedef struct PACKED {
    uint16 limit;
    idt_gate* ptr;
} idt_reg;

#define IDT_SIZE 256

/* Wrapper for LIDT assembly instruction. */
#define idt_load(id) asmv("lidt %0"::"m"(*id))

/* Initialize IDT. */
void idt_init();

/* Register interrupt in the IDT. */
void idt_set(int_hdl isr, uint8 ic);