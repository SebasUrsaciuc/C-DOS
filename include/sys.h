#pragma once

#include "def.h"

/* Halts the CPU until an interrupt is called (asm wrapper). */
void hlt();

/* Kernel panic. */
void panic(const char* mot);

/* Wait for N time (in ms). */
void wait(uint16 ms);