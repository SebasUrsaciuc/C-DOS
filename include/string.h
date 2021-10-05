#pragma once

#include "def.h"

typedef int16 strsz;

/* Compare two strings: returns true if they are equal. */
bool strequ(const char* str1, const char* str2);

/* Compare two strings: returns true if they are equal (ignoring case). */
bool streqi(const char* str1, const char* str2);

/* Concatenates two strings. */
void strcat(char* dest, const char* src);

/* Returns string length. */
uint strlen(const char* str);

/* Clears a string. */
void strclr(char* str);

/* Copies a string. */
void strcpy(char* dest, const char* src);

/* Converts integer to string. */
void itos(int i, char* buf);

/* Converts integer to hex string. */
void xtos(int x, char* buf);

/* Converts string to integer. */
int stoi(const char* a);

/* Makes char upper case. */
char charup(char ch);

/* Makes char lower case. */
char charlow(char ch);