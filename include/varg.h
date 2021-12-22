#pragma once

typedef void* va_list;

#define va_init(f) (va_list) (&f)
#define va_next(l, t) *((t*) (l += sizeof(t)))