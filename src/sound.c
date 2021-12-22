#include "sound.h"

#include "port.h"
#include "pit.h"
#include "ps2.h"
#include "sys.h"

void snd_play(uint16 freq) {
    uint32 div = PIT_INTERVAL / freq;

    port_outb(PIT_CMDPORT, PIT_CMD_CH_2 | PIT_CMD_ACC_BOTH | PIT_CMD_MODE_3);
    port_outb(PIT_DATAPORT_3, div & 0xFF);
    port_outb(PIT_DATAPORT_3, (div >> 8) & 0xFF);

    port_outb(PS2_CTRL_SYSPORT, port_inb(PS2_CTRL_SYSPORT) | 0b00000011);
}

void snd_stop() {
    port_outb(PS2_CTRL_SYSPORT, port_inb(PS2_CTRL_SYSPORT) & 0b11111100);
}

void snd_beep(uint16 freq, uint16 ms) {
    snd_play(freq);
    sys_wait(ms);
    snd_stop();
}