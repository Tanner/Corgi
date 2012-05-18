#include "types.h"

#ifndef CORGI_MEMORY_H_

#define CORGI_MEMORY_H_

typedef struct _MEMORY {
	u32 address_space;
	u32 *memory;
} MEMORY;

MEMORY * memory_init(u32 address_space);
void memory_free(MEMORY *memory);

#endif