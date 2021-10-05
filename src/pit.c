#include "pit.h"

#include "port.h"
#include "int.h"

uint32 ticks = 0;

void ISR pitisr(intf* ifr) {
    ticks++;

    endpic();
}

void initpit() {
    uint32 div = PIT_INTERVAL / 100;

    outb(PIT_COMPORT, PIT_COM_CH_0 | PIT_COM_ACC_HIGH | PIT_COM_MODE_2);
    outb(PIT_DATAPORT_1, div & 0xFF);
    outb(PIT_DATAPORT_1, (div >> 8) & 0xFF);

    regint(pitisr, 32);
}

uint32 gettime() {
    return ticks * 10;
}