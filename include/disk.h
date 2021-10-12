#pragma once

#include "def.h"

#define SECT_SIZE 512
#define LBA_28_BITS_MASK 0x0FFFFFFF

#define DISK_RWPORT 0x1F0
#define DISK_DATAPORT_SECTS 0x1F2
#define DISK_DATAPORT_ADDR_0_8 0x1F3
#define DISK_DATAPORT_ADDR_8_16 0x1F4
#define DISK_DATAPORT_ADDR_16_24 0x1F5
#define DISK_DATAPORT_ADDR_24_32 0x1F6
#define DISK_COMPORT 0x1F7

#define DISK_COM_READ 0x20
#define DISK_COM_WRITE 0x30

/* Prepares the disk for a read/write operation. */
void diskprp(uint32 addr, uint8 sects, uint8 op);

/* Read disk in ATA LBA mode. */
void diskrd(uint32 addr, uint8 sects, void* dest);

/* Write disk in ATA LBA mode. */
void diskwr(uint32 addr, uint8 sects, void* src);