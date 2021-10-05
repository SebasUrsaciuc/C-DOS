#include "sound.h"

#include "port.h"
#include "pit.h"
#include "ps2.h"
#include "sys.h"

void playsnd(uint16 freq) {
    uint32 div = PIT_INTERVAL / freq;

    outb(PIT_COMPORT, PIT_COM_CH_2 | PIT_COM_ACC_BOTH | PIT_COM_MODE_3);
    outb(PIT_DATAPORT_3, div & 0xFF);
    outb(PIT_DATAPORT_3, (div >> 8) & 0xFF);

    outb(PS2CTRL_SYSPORT, inb(PS2CTRL_SYSPORT) | 0b00000011);
}

void stopsnd() {
    outb(PS2CTRL_SYSPORT, inb(PS2CTRL_SYSPORT) & 0b11111100);
}

void beep(uint16 freq, uint16 ms) {
    playsnd(freq);
    wait(ms);
    stopsnd();
}