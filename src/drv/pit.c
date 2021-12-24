#include "drv/pit.h"

#include "cpu/port.h"
#include "cpu/idt.h"

uint32 ticks = 0;

void INT_SR pit_ISR(int_fr* ifr) {
    ticks++;

    int_picEnd();
}

void pit_init() {
    uint32 div = PIT_INTERVAL / 100;

    port_outb(PIT_CMDPORT, PIT_CMD_CH_0 | PIT_CMD_ACC_HIGH | PIT_CMD_MODE_2);
    port_outb(PIT_DATAPORT_1, div & 0xFF);
    port_outb(PIT_DATAPORT_1, (div >> 8) & 0xFF);

    idt_set(pit_ISR, 32);
}

uint32 pit_getTime() {
    return ticks * 10;
}