#include "cpu/idt.h"

#include "sys.h"

idt_gate idt[IDT_SIZE];
idt_reg idt_dsc = { sizeof(idt) - 1, idt };

void INT_SR idt_expISR(int_fr* ifr) {
    sys_panic("UNHANDLED_EXCEPTION");
}

void INT_SR idt_picISR(int_fr* ifr) {
    int_picEnd();
}

void idt_init() {
    for(uint16 i = 0; i < 32; i++) {
        idt_set(idt_expISR, i);
    }

    for(uint16 i = 32; i < 48; i++) {
        idt_set(idt_picISR, i);
    }
    
    idt_load(&idt_dsc);
    int_set(true);
}

void idt_set(int_hdl isr, uint8 ic) {
    idt[ic] = (idt_gate) {
        (uint32) isr & 0xFFFF,  // first 16 bits of function pointer
        0x0008,                 // code segment offset in GDT
        0x0000,                 // reserved
        0x008E,                 // flags
        (uint32) isr >> 16      // last 16 bits of function pointer
    };
}