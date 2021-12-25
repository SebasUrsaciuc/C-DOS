#pragma once

#include "def.h"

typedef struct {
    uint8 sec;
    uint8 min;
    uint8 hour;
    uint8 day;
    uint8 month;
    uint16 year;
} cmos_time;

#define CMOS_CMDPORT 0x70
#define CMOS_DATAPORT 0x71

#define CMOS_REG_SECONDS 0x00
#define CMOS_REG_MINUTES 0x02
#define CMOS_REG_HOURS 0x04
#define CMOS_REG_WEEKDAY 0x06
#define CMOS_REG_DAY 0x07
#define CMOS_REG_MONTH 0x08
#define CMOS_REG_YEAR 0x09
#define CMOS_REG_A 0x0A
#define CMOS_REG_B 0x0B

/* Converts BCD time format to binary format. */
#define cmos_fromBCD(v) (((v) & 0x0F) + (((v) / 16) * 10))

/* Checks if the CMOS is being updated by the RTC. */
#define cmos_isUpdating() (cmos_read(CMOS_REG_A) & 0x80)

/* Reads CMOS register. */
uint8 cmos_read(uint8 reg);

/* Get actual CMOS time. */
cmos_time cmos_getTime();