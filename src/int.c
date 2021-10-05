#include "int.h"

#include "port.h"
#include "sys.h"

intd idt[IDT_SIZE];
idtr idtdsc = { sizeof(idt) - 1, idt };

void ISR expisr(intf* ifr) {
    panic("UNHANDLED_EXCEPTION");
}

void ISR picisr(intf* ifr) {
    endpic();
}

void setintf(bool enabled) {
    if(enabled) {
        asm("sti");
    } else {
        asm("cli");
    }
}

void regint(void (*isr)(intf*), uint8 ic) {
    idt[ic] = (intd) {
        isrtolow(isr),      // first 16 bits of function pointer
        0x0008,             // code segment offset in GDT
        0x0000,             // reserved
        0x008E,             // flags
        isrtotop(isr)       // last 16 bits of function pointer
    };
}

void endpic() {
    outb(MASTERPIC_COMPORT, PIC_EOI);
    outb(SLAVEPIC_COMPORT, PIC_EOI);
}

void initidt() {
    initpic();

    for(uint16 i = 0; i < 32; i++) {
        regint(expisr, i);
    }

    for(uint16 i = 32; i < 48; i++) {
        regint(picisr, i);
    }
    
    lidt(idtdsc);
    setintf(true);
}

void initpic() {
    uint8 mastermask, slavemask;

    mastermask = inb(MASTERPIC_DATAPORT);
    slavemask = inb(SLAVEPIC_DATAPORT);

    outb(MASTERPIC_COMPORT, PIC_INIT);
    outb(SLAVEPIC_COMPORT, PIC_INIT);

    outb(MASTERPIC_DATAPORT, MASTERPIC_OFFSET);    // 32-39 ints - MASTER PIC
    outb(SLAVEPIC_DATAPORT, SLAVEPIC_OFFSET);     // 40-47 ints - SLAVE PIC
    outb(MASTERPIC_DATAPORT, 4);
    outb(SLAVEPIC_DATAPORT, 2);
    outb(MASTERPIC_DATAPORT, 1);
    outb(SLAVEPIC_DATAPORT, 1);

    outb(MASTERPIC_DATAPORT, mastermask);
    outb(SLAVEPIC_DATAPORT, slavemask);
}

void lidt(idtr id) {
    asm volatile (
        "lidt %0"
        :
        : "m"(id)
    );
}