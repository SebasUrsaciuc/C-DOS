#pragma once

/* Prints a screen value onto the screen following the cursor. */
void io_putChar(char ch);

/* Prints a string onto the screen with newline. */
void io_println(const char* str);

/* Prints a string onto the screen without newline. */
void io_print(const char* str);

/* Formated print. */
void io_printf(const char* format, ...);

/* Get a char from keyboard. */
char io_getChar();

/* Get a string as input from the keyboard. */
void io_getStr(char* buf);