#include "drv/cmos.h"

#include "cpu/port.h"

uint8 cmos_read(uint8 reg) {
    port_outb(CMOS_CMDPORT, reg);

    return port_inb(CMOS_DATAPORT);
}

cmos_time cmos_getTime() {
    uint8 regB = cmos_read(CMOS_REG_B);

    cmos_time t;
    t.sec = cmos_read(CMOS_REG_SECONDS);
    t.min = cmos_read(CMOS_REG_MINUTES);
    t.hour = cmos_read(CMOS_REG_HOURS);
    t.day = cmos_read(CMOS_REG_DAY);
    t.month = cmos_read(CMOS_REG_MONTH);
    t.year = cmos_read(CMOS_REG_YEAR);

    bool pm = t.hour & 0x80;
    t.hour &= ~0x80;

    if(regB & 0b10) {
        t.sec = cmos_toBCD(t.sec);
        t.min = cmos_toBCD(t.min);
        t.hour = cmos_toBCD(t.hour);
        t.day = cmos_toBCD(t.day);
        t.month = cmos_toBCD(t.month);
        t.year = cmos_toBCD(t.year);
    }

    if(regB & 0b100) {
        t.hour %= 12;

        if(pm) {
            t.hour += 12;
        }
    }

    t.year += 2000;

    return t;
}