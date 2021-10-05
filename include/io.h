#pragma once

#include "def.h"

#define VGA_SCR_ROWS 25
#define VGA_SCR_COLS 80
#define VGA_SCR_CELLS (VGA_SCR_ROWS * VGA_SCR_COLS)

#define VGA_MEM_START 0xB8000
#define VGA_MEM_END (VGA_MEM_START + VGA_SCR_CELLS * 2)

#define CUR_DATAPORT_1 0x3D4
#define CUR_DATAPORT_2 0x3D5

#define CUR_COM_STATE_1 0x0A
#define CUR_COM_STATE_2 0x0B
#define CUR_COM_POS_1 0x0F
#define CUR_COM_POS_2 0x0E

/* VECtor TO CURsor & CURsor TO X/Y. */
#define xytocur(X, Y) ((X) + ((Y) * VGA_SCR_COLS))
#define curtox(pos) ((pos) % VGA_SCR_COLS)
#define curtoy(pos) ((pos) / VGA_SCR_COLS)

typedef struct attr(packed) {
   uint8 ch: 8;
   uint8 clr: 8;
} scrval;

typedef struct attr(packed) {
   uint8 ssl: 4;
   uint8 esl: 4;
} cursh;

extern const cursh CUR_SH_DISABLED;
extern const cursh CUR_SH_UNDERLINE;
extern const cursh CUR_SH_BOX;

/* Set cursor state. */
void setcurs(cursh state);

/* Set cursor position. */
void setcurp(uint16 pos);

/* Add to cursor position. */
void addcurp(uint16 add);

/* Get cursor position. */
uint16 getcurp();

/* Sets console global color. */
void setclr(uint8 color);

/* Clears the screen. */
void clrs();

/* Scrolls the screen in up direction. */
void movs(uint8 rows);

/* Get char from specified position. */
scrval peek(uint16 pos);

/* Prints a char onto the screen. */
void poke(scrval sv, uint16 pos);

/* Prints a char onto the screen following the cursor. */
void putc(char ch);

/* Prints a string onto the screen with newline. */
void puts(const char* str);

/* Prints a string onto the screen without newline. */
void sputs(const char* str);

/* Formated print */
void printf(const char* format, ...);

/* Get a char from keyboard. */
char getc();

/* Get a string as input from the keyboard. */
void gets(char* buf);