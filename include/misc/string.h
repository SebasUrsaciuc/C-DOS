#pragma once

#include "def.h"

typedef int16 str_sz;

/* Makes char upper case. */
#define str_charUp(ch) (ch >= 'A' && ch <= 'Z'? ch + 0x20 : ch)

/* Makes char lower case. */
#define str_charDown(ch) (ch >= 'a' && ch <= 'z'? ch - 0x20 : ch)

/* Compare two strings: returns true if they are equal. */
bool str_equ(const char* str1, const char* str2);

/* Compare two strings: returns true if they are equal (ignoring case). */
bool str_eqi(const char* str1, const char* str2);

/* Concatenates two strings. */
void str_cat(char* dest, const char* src);

/* Returns string length. */
uint str_len(const char* str);

/* Clears a string. */
void str_clear(char* str);

/* Copies a string. */
void str_copy(char* dest, const char* src);

/* Converts integer to string. */
void str_fromInt(int i, char* buf);

/* Converts integer to hex string. */
void str_fromHex(int x, char* buf);

/* Converts string to integer. */
int str_toInt(const char* a);