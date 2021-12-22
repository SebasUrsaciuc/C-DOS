#include "int.h"

#include "port.h"
#include "sys.h"

int_gate idt[INT_IDT_SIZE];
int_desc idtdsc = { sizeof(idt) - 1, idt };

void INT_SR int_expISR(int_fr* ifr) {
    sys_panic("UNHANDLED_EXCEPTION");
}

void INT_SR int_picISR(int_fr* ifr) {
    int_picEnd();
}

void int_reg(int_hdl isr, uint8 ic) {
    idt[ic] = (int_gate) {
        (uint32) isr & 0xFFFF,  // first 16 bits of function pointer
        0x0008,                 // code segment offset in GDT
        0x0000,                 // reserved
        0x008E,                 // flags
        (uint32) isr >> 16      // last 16 bits of function pointer
    };
}

void int_picEnd() {
    port_outb(INT_MASTERPIC_CMDPORT, INT_COM_PIC_EOI);
    port_outb(INT_SLAVEPIC_CMDPORT, INT_COM_PIC_EOI);
}

void int_init() {
    int_picInit();

    for(uint16 i = 0; i < 32; i++) {
        int_reg(int_expISR, i);
    }

    for(uint16 i = 32; i < 48; i++) {
        int_reg(int_picISR, i);
    }
    
    int_loadIDT(&idtdsc);
    int_set(true);
}

void int_picInit() {
    uint8 mastermask = port_inb(INT_MASTERPIC_DATAPORT);
    uint8 slavemask = port_inb(INT_SLAVEPIC_DATAPORT);

    port_outb(INT_MASTERPIC_CMDPORT, INT_COM_PIC_INIT);
    port_outb(INT_SLAVEPIC_CMDPORT, INT_COM_PIC_INIT);

    port_outb(INT_MASTERPIC_DATAPORT, INT_MASTERPIC_OFFSET);    // 32-39 ints - MASTER PIC
    port_outb(INT_SLAVEPIC_DATAPORT, INT_SLAVEPIC_OFFSET);     // 40-47 ints - SLAVE PIC
    port_outb(INT_MASTERPIC_DATAPORT, 4);
    port_outb(INT_SLAVEPIC_DATAPORT, 2);
    port_outb(INT_MASTERPIC_DATAPORT, 1);
    port_outb(INT_SLAVEPIC_DATAPORT, 1);

    port_outb(INT_MASTERPIC_DATAPORT, mastermask);
    port_outb(INT_SLAVEPIC_DATAPORT, slavemask);
}