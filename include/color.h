#pragma once

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

#define VGA_CLR_STANDARD (VGA_CLR_BG_BLACK | VGA_CLR_FG_SILVER)