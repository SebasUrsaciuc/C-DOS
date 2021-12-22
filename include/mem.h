#pragma once

#include "def.h"

/* Fills a portion of memory with a value. */
void mem_set(void* ptr, uint8 val, uint32 num);

/* Copies a portion of memory in an another location. */
void mem_copy(void* dest, void* src, uint32 num);