#include "drv/vga.h"

#include "cpu/port.h"

const vga_crs VGA_CRS_OFF = { 0x0, 0x0 };
const vga_crs VGA_CRS_LN = { 0xE, 0xF };
const vga_crs VGA_CRS_BOX = { 0x0, 0xF };

vga_char global = (vga_char) { ' ', VGA_CLR_STD };
vga_char* data = (vga_char*) VGA_MEM_START;

void vga_setCrs(vga_crs state) {
    if(state.startLn == 0 && state.endLn == 0) {
        port_outb(VGA_CRS_DATAPORT_1, VGA_CRS_CMD_STATE_1);
        port_outb(VGA_CRS_DATAPORT_2, VGA_CRS_NULL);
        return;
    }

    port_outb(VGA_CRS_DATAPORT_1, VGA_CRS_CMD_STATE_1);
    port_outb(VGA_CRS_DATAPORT_2, (port_inb(VGA_CRS_DATAPORT_2) & 0xC0) | state.startLn);

    port_outb(VGA_CRS_DATAPORT_1, VGA_CRS_CMD_STATE_2);
    port_outb(VGA_CRS_DATAPORT_2, (port_inb(VGA_CRS_DATAPORT_2) & 0xE0) | state.endLn);
}

void vga_setPos(vga_pos pos) {
    port_outb(VGA_CRS_DATAPORT_1, VGA_CRS_CMD_POS_1);
    port_outb(VGA_CRS_DATAPORT_2, (pos & 0xFF));
    port_outb(VGA_CRS_DATAPORT_1, VGA_CRS_CMD_POS_2);
    port_outb(VGA_CRS_DATAPORT_2, (pos >> 8) & 0xFF);

    while(vga_getPos() >= VGA_SCR_CELLS) {
        vga_scroll(1);
    }
}

vga_pos vga_getPos() {
    vga_pos pos = 0;

    port_outb(VGA_CRS_DATAPORT_1, VGA_CRS_CMD_POS_1);
    pos |= port_inb(VGA_CRS_DATAPORT_2);
    port_outb(VGA_CRS_DATAPORT_1, VGA_CRS_CMD_POS_2);
    pos |= ((uint16) port_inb(VGA_CRS_DATAPORT_2)) << 8;

    return pos;
}

void vga_setColor(vga_clr color) {
    global.clr = color;
}

void vga_clear() {
    vga_setPos(0);

    for(vga_pos i = 0; i <= VGA_SCR_CELLS; i++) {
        vga_poke(global, i);
    }
}

void vga_scroll(uint8 rows) {
    uint16 cells = rows * VGA_SCR_W;

    for(uint16 i = 0; i < VGA_SCR_CELLS; i++) {
        vga_poke(vga_peek(i), i - cells);
    }

    for(uint16 i = 0; i < cells; i++) {
        vga_poke(global, VGA_SCR_CELLS - cells + i);
    }

    vga_incPos(-cells);
}

vga_char vga_peek(vga_pos pos) {
    return pos < VGA_SCR_CELLS? data[pos] : global;
}

void vga_poke(vga_char ch, vga_pos pos) {
    if(ch.clr == VGA_CLR_NULL) {
        ch.clr = global.clr;
    }

    if(pos < VGA_SCR_CELLS) {
        data[pos] = ch;
    }
}