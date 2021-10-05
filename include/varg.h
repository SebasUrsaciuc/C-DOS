#pragma once

typedef void* valist;

#define vainit(f) (valist) (&f)
#define vanext(l, t) *((t*) (l += sizeof(t)))