#include "disk.h"

#include "port.h"

void disk_prep(uint32 addr, uint8 sects, uint8 op) {
    addr &= DISK_LBA_28BIT_MASK;
    addr |= 0b11100000 << 24;

    port_outb(DISK_DATAPORT_SECTS, sects);
    port_outb(DISK_DATAPORT_ADDR_0_8, addr);
    port_outb(DISK_DATAPORT_ADDR_8_16, addr >> 8);
    port_outb(DISK_DATAPORT_ADDR_16_24, addr >> 16);
    port_outb(DISK_DATAPORT_ADDR_24_32, addr >> 24);

    port_outb(DISK_CMDPORT, op);
}

void disk_read(uint32 addr, uint8 sects, void* dest) {
    disk_prep(addr, sects, DISK_CMD_READ);

    uint16* buf = (uint16*) dest;

    for(uint8 i = 0; i < sects; i++) {
        while(!(port_inb(DISK_CMDPORT) & 0b00001000));

        for(uint16 j = 0; j < 256; j++) {
            buf[j] = port_inw(DISK_RWPORT);
        }

        buf += 256;
    }
}

void disk_write(uint32 addr, uint8 sects, void* src) {
    disk_prep(addr, sects, DISK_CMD_WRITE);

    uint16* buf = (uint16*) src;

    for(uint8 i = 0; i < sects; i++) {
        while(!(port_inb(DISK_CMDPORT) & 0b00001000));

        for(uint16 j = 0; j < 256; j++) {
            port_outw(DISK_RWPORT, buf[j]);
        }
        
        buf += 256;
    }
}