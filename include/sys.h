#pragma once

#include "def.h"

/* Halts the CPU until an interrupt is called (asm wrapper). */
#define sys_hlt() asm("hlt")

/* Kernel panic. */
void sys_panic(const char* mot);

/* Disables interrupts and halts. */
void sys_kill();

/* Wait for N time (in ms). */
void sys_wait(uint16 ms);