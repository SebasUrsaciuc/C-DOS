#pragma once

#include "cpu/port.h"

#define PS2_CTRL_DATAPORT 0x60
#define PS2_CTRL_SYSPORT 0x61
#define PS2_CTRL_CMDPORT 0x64

#define PS2_CMD_RESET 0xFE

/* Reboots the system. */
#define ps2_reset() port_outb(PS2_CTRL_CMDPORT, PS2_CMD_RESET);