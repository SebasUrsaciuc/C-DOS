#pragma once

#include "cpu/int.h"

typedef struct PACKED {
    uint16 limit;
    int_gate* idtptr;
} idt_dsc, idt_desc;

#define IDT_SIZE 256

/* Wrapper for LIDT assembly instruction. */
#define idt_load(id) asmv("lidt %0"::"m"(*id))

/* Initialize IDT. */
void idt_init();

/* Register interrupt in the IDT. */
void idt_set(int_hdl isr, uint8 ic);