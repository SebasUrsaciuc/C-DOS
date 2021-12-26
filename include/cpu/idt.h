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

#define IDT_GATE_PRESENT 0b10000000
#define IDT_GATE_ABSENT 0b00000000
#define IDT_GATE_PRIV_KERNEL 0b0000000
#define IDT_GATE_PRIV_USERLAND 0b1100000
#define IDT_GATE_TYPE_TASK 0b0101
#define IDT_GATE_TYPE_INT_16 0b0110
#define IDT_GATE_TYPE_TRAP_16 0b0111
#define IDT_GATE_TYPE_INT_32 0b1110
#define IDT_GATE_TYPE_TRAP_32 0b1111

/* Wrapper for LIDT assembly instruction. */
#define idt_load(id) asmv("lidt %0"::"m"(*id))

/* Register null gate in the IDT. */
#define idt_setNull(ic) idt_set(NULL, ic, IDT_GATE_ABSENT)

/* Register interrupt gate in the IDT. */
#define idt_setHard(ptr, ic, priv) idt_set(ptr, ic, IDT_GATE_PRESENT | priv | IDT_GATE_TYPE_INT_32)

/* Register trap gate in the IDT. */
#define idt_setSoft(ptr, ic, priv) idt_set(ptr, ic, IDT_GATE_PRESENT | priv | IDT_GATE_TYPE_TRAP_32)

/* Initialize IDT. */
void idt_init();

/* Register gate in the IDT. */
void idt_set(int_hdl isr, uint8 ic, uint8 flags);