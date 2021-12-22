#include "port.h"

void port_outb(uint16 port, uint8 data) {
    asm volatile (
        "outb %0, %1"
        :
        : "a"(data), "Nd"(port)
    );
}

uint8 port_inb(uint16 port) {
    uint8 data;

    asm volatile (
        "inb %1, %0"
        : "=a"(data)
        : "Nd"(port)
    );
    
    return data;
}

void port_outw(uint16 port, uint16 data) {
    asm volatile (
        "outw %0, %1"
        :
        : "a"(data), "Nd"(port)
    );
}

uint16 port_inw(uint16 port) {
    uint16 data;

    asm volatile (
        "inw %1, %0"
        : "=a"(data)
        : "Nd"(port)
    );
    
    return data;
}