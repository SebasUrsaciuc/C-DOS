#pragma once

#include "def.h"

typedef struct PACKED {
    uint32 eip;
    uint16 cs;
    uint32 flags;
    uint32 esp;
    uint16 ss;
} int_fr, int_frame;

typedef struct PACKED {
    uint16 lowoff;
    uint16 codseg;
    uint8 res;
    uint8 attr;
    uint16 topoff;
} int_gt, int_gate;

typedef struct PACKED {
    uint16 limit;
    int_gate* idtptr;
} int_dsc, int_desc;

typedef void (*int_hdl)(int_fr*);

#define INT_MASTERPIC_CMDPORT 0x20
#define INT_SLAVEPIC_CMDPORT 0xA0
#define INT_MASTERPIC_DATAPORT 0x21
#define INT_SLAVEPIC_DATAPORT 0xA1

#define INT_MASTERPIC_OFFSET 32
#define INT_SLAVEPIC_OFFSET (INT_MASTERPIC_OFFSET + 8)

#define INT_COM_PIC_INIT 0x11
#define INT_COM_PIC_EOI 0x20

#define INT_IDT_SIZE 256

#define INT_SR attr(interrupt)

/* Call interrupt. */
#define int_call(ic) asmv("int %0"::"i"(ic))

/* Wrapper for LIDT assembly instruction. */
#define int_loadIDT(id) asmv("lidt %0"::"m"(*id))

/* Enable or disable interrupts. */
#define int_set(en) if(en) asm("sti"); else asm("cli")

/* Register interrupt (requires function of type ISR). */
void int_reg(int_hdl isr, uint8 ic);

/* End hardware interrupt function (mandatory at hardware ISR end). */
void int_picEnd();

/* Initialize IDT (remaps the PIC chip and loads the IDT). */
void int_init();

/* Initialize the PIC chip. */
void int_picInit();