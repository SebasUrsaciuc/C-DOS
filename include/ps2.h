#pragma once

#define PS2CTRL_DATAPORT 0x60
#define PS2CTRL_SYSPORT 0x61
#define PS2CTRL_COMPORT 0x64

#define PS2CTRL_COM_RESET 0xFE

/* Reboots the system. */
void reset();