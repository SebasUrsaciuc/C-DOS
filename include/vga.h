#pragma once

#include "def.h"

typedef struct attr(packed) {
   uint8 ch: 8;
   uint8 clr: 8;
} vga_char;

typedef struct attr(packed) {
   uint8 startLn: 4;
   uint8 endLn: 4;
} vga_crs, vga_cursor;

typedef uint8 vga_clr;
typedef uint16 vga_pos;

#define VGA_SCR_W 80
#define VGA_SCR_H 25
#define VGA_SCR_CELLS (VGA_SCR_W * VGA_SCR_H)

#define VGA_MEM_START 0xB8000

#define VGA_CRS_NULL 0x20

#define VGA_CRS_DATAPORT_1 0x3D4
#define VGA_CRS_DATAPORT_2 0x3D5

#define VGA_CRS_CMD_STATE_1 0x0A
#define VGA_CRS_CMD_STATE_2 0x0B
#define VGA_CRS_CMD_POS_1 0x0F
#define VGA_CRS_CMD_POS_2 0x0E

#define VGA_CLR_FG_BLACK        0b0000 // ----
#define VGA_CLR_FG_BLUE         0b0001 // ---B
#define VGA_CLR_FG_GREEN        0b0010 // --G-
#define VGA_CLR_FG_CYAN         0b0011 // --GB
#define VGA_CLR_FG_RED          0b0100 // -R--
#define VGA_CLR_FG_PURPLE       0b0101 // -R-B
#define VGA_CLR_FG_GOLD         0b0110 // -RG-
#define VGA_CLR_FG_SILVER       0b0111 // -RGB
#define VGA_CLR_FG_GREY         0b1000 // I---
#define VGA_CLR_FG_WARMBLUE     0b1001 // I--B
#define VGA_CLR_FG_EMERALD      0b1010 // I-G-
#define VGA_CLR_FG_AQUAMARINE   0b1011 // I-GB
#define VGA_CLR_FG_TOMATO       0b1100 // IR--
#define VGA_CLR_FG_FUCHSIA      0b1101 // IR-B
#define VGA_CLR_FG_YELLOW       0b1110 // IRG-
#define VGA_CLR_FG_WHITE        0b1111 // IRGB

#define VGA_CLR_BG_BLACK        0b00000000 // ----
#define VGA_CLR_BG_BLUE         0b00010000 // ---B
#define VGA_CLR_BG_GREEN        0b00100000 // --G-
#define VGA_CLR_BG_CYAN         0b00110000 // --GB
#define VGA_CLR_BG_RED          0b01000000 // -R--
#define VGA_CLR_BG_PURPLE       0b01010000 // -R-B
#define VGA_CLR_BG_GOLD         0b01100000 // -RG-
#define VGA_CLR_BG_SILVER       0b01110000 // -RGB
#define VGA_CLR_BG_GREY         0b10000000 // I---
#define VGA_CLR_BG_WARMBLUE     0b10010000 // I--B
#define VGA_CLR_BG_EMERALD      0b10100000 // I-G-
#define VGA_CLR_BG_AQUAMARINE   0b10110000 // I-GB
#define VGA_CLR_BG_TOMATO       0b11000000 // IR--
#define VGA_CLR_BG_FUCHSIA      0b11010000 // IR-B
#define VGA_CLR_BG_YELLOW       0b11100000 // IRG-
#define VGA_CLR_BG_WHITE        0b11110000 // IRGB

#define VGA_CLR_NULL 0
#define VGA_CLR_STD (VGA_CLR_BG_BLACK | VGA_CLR_FG_SILVER)

extern const vga_crs VGA_CRS_OFF;
extern const vga_crs VGA_CRS_LN;
extern const vga_crs VGA_CRS_BOX;

/* Transforms X and Y coordonates into a vga screen position. */
#define vga_posFromXY(X, Y) ((X) + ((Y) * VGA_SCR_W))

/* Transforms a vga screen position into the the X coordonate. */
#define vga_posToX(pos) ((pos) % VGA_SCR_W)

/* Transforms a vga screen position into the the Y coordonate. */
#define vga_posToY(pos) ((pos) / VGA_SCR_W)

/* Add to cursor position. */
#define vga_incPos(inc) vga_setPos(vga_getPos() + inc)

/* Set cursor state. */
void vga_setCrs(vga_crs state);

/* Set cursor position. */
void vga_setPos(vga_pos pos);

/* Get cursor position. */
vga_pos vga_getPos();

/* Sets console global color. */
void vga_setColor(vga_clr color);

/* Clears the screen. */
void vga_clear();

/* Scrolls the screen in up direction. */
void vga_scroll(uint8 rows);

/* Get screen value from specified position. */
vga_char vga_peek(vga_pos pos);

/* Prints a screen value onto the screen. */
void vga_poke(vga_char ch, vga_pos pos);