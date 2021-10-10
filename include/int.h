#pragma once

#include "def.h"

#define ISR attr(interrupt)

#define MASTERPIC_COMPORT 0x20
#define SLAVEPIC_COMPORT 0xA0
#define MASTERPIC_DATAPORT 0x21
#define SLAVEPIC_DATAPORT 0xA1

#define MASTERPIC_OFFSET 32
#define SLAVEPIC_OFFSET (MASTERPIC_OFFSET + 8)

#define PIC_INIT 0x11
#define PIC_EOI 0x20

#define IDT_SIZE 256

typedef struct attr(packed) {
    uint32 eip;
    uint32 cs;
    uint32 flags;
    uint32 esp;
    uint32 ss;
} intf;

typedef struct attr(packed) {
    uint16 lowoff;
    uint16 codseg;
    uint8 res;
    uint8 attr;
    uint16 topoff;
} intd;

typedef struct attr(packed) {
    uint16 limit;
    intd* idtptr;
} idtr;

/* Enable or disable interrupts. */
void setintf(bool enabled);

/* Register interrupt (requires function of type ISR). */
void regint(void (*isr)(intf*), uint8 ic);

/* End hardware interrupt function (mandatory at hardware ISR end). */
void endpic();

/* Initialize IDT (remaps the PIC chip and loads the IDT). */
void initidt();

/* Initialize the PIC chip. */
void initpic();

/* Wrapper for LIDT assembly instruction. */
void lidt(idtr id);