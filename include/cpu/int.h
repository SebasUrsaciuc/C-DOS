#pragma once

#include "def.h"

typedef struct PACKED {
    uint32 eip;
    uint16 cs;
    uint32 flags;
    uint32 esp;
    uint16 ss;
} int_fr, int_frame;

typedef void (*int_hdl)(int_fr*);

#define INT_MASTERPIC_CMDPORT 0x20
#define INT_SLAVEPIC_CMDPORT 0xA0
#define INT_MASTERPIC_DATAPORT 0x21
#define INT_SLAVEPIC_DATAPORT 0xA1

#define INT_MASTERPIC_OFFSET 32
#define INT_SLAVEPIC_OFFSET (INT_MASTERPIC_OFFSET + 8)

#define INT_COM_PIC_INIT 0x11
#define INT_COM_PIC_EOI 0x20

#define INT_SR attr(interrupt)

/* Initialize interrupts. */
#define int_init() int_picRemap()

/* Call interrupt. */
#define int_call(ic) asmv("int %0"::"i"(ic))

/* Enable or disable interrupts. */
#define int_set(en) if(en) asm("sti"); else asm("cli")

/* End hardware interrupt function (mandatory at hardware ISR end). */
void int_picEnd();

/* Initialize the PIC chip. */
void int_picRemap();