#include "cpu/port.h"

void port_outb(uint16 port, uint8 data) {
    asm volatile (
        "out %0, %1"
        :
        : "Nd"(port), "a"(data)
    );
}

uint8 port_inb(uint16 port) {
    uint8 data;

    asm volatile (
        "in %0, %1"
        : "=a"(data)
        : "Nd"(port)
    );
    
    return data;
}

void port_outw(uint16 port, uint16 data) {
    asm volatile (
        "out %0, %1"
        :
        : "Nd"(port), "a"(data)
    );
}

uint16 port_inw(uint16 port) {
    uint16 data;

    asm volatile (
        "in %0, %1"
        : "=a"(data)
        : "Nd"(port)
    );
    
    return data;
}