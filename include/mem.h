#pragma once

#include "def.h"

/* Fills a portion of memory with a value. */
void memset(void* ptr, uint8 val, uint32 num);

/* Copies a portion of memory in an another location. */
void memcpy(void* dest, void* src, uint32 num);