#include "cpu/int.h"

#include "cpu/port.h"

void int_picEnd() {
    port_outb(INT_MASTERPIC_CMDPORT, INT_COM_PIC_EOI);
    port_outb(INT_SLAVEPIC_CMDPORT, INT_COM_PIC_EOI);
}

void int_picRemap() {
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