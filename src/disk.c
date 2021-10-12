#include "disk.h"

#include "port.h"

void diskprp(uint32 addr, uint8 sects, uint8 op) {
    addr &= LBA_28_BITS_MASK;
    addr |= 0b11100000 << 24;

    outb(DISK_DATAPORT_SECTS, sects);
    outb(DISK_DATAPORT_ADDR_0_8, addr);
    outb(DISK_DATAPORT_ADDR_8_16, addr >> 8);
    outb(DISK_DATAPORT_ADDR_16_24, addr >> 16);
    outb(DISK_DATAPORT_ADDR_24_32, addr >> 24);

    outb(DISK_COMPORT, op);
}

void diskrd(uint32 addr, uint8 sects, void* dest) {
    diskprp(addr, sects, DISK_COM_READ);

    uint16* buf = (uint16*) dest;

    for(uint8 i = 0; i < sects; i++) {
        while(!(inb(DISK_COMPORT) & 0b00001000));

        for(uint16 j = 0; j < 256; j++) {
            buf[j] = inw(DISK_RWPORT);
        }

        buf += 256;
    }
}

void diskwr(uint32 addr, uint8 sects, void* src) {
    diskprp(addr, sects, DISK_COM_WRITE);

    uint16* buf = (uint16*) src;

    for(uint8 i = 0; i < sects; i++) {
        while(!(inb(DISK_COMPORT) & 0b00001000));

        for(uint16 j = 0; j < 256; j++) {
            outw(DISK_RWPORT, buf[j]);
        }

        buf += 256;
    }
}