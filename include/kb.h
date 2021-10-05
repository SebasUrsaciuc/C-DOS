#pragma once

#include "def.h"

#define CHAR_MAP_SIZE 0xC0

typedef enum { press, release } kbev;
typedef struct {
    char ch;
    uint16 sc;
    kbev ev;
} kbkey;

extern const char CHARMAP[CHAR_MAP_SIZE];
extern const char SHIFTED_CHARMAP[CHAR_MAP_SIZE];

/* Initializes the keyboard. */
void initkb();

/* Waits for key press and returns it. */
kbkey getkey();