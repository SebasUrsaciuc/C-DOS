#pragma once

#include "def.h"

/* Start playing sound. */
void playsnd(uint16 freq);

/* Stop playing sound. */
void stopsnd();

/* Beep (this will pause the thread!). */
void beep(uint16 freq, uint16 ms);