#pragma once

#include "def.h"

/* Start playing sound. */
void snd_play(uint16 freq);

/* Stop playing sound. */
void snd_stop();

/* Beep (this will pause the thread!). */
void snd_beep(uint16 freq, uint16 ms);