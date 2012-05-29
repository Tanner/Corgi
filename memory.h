#include <stdbool.h>

#include "types.h"

#ifndef CORGI_MEMORY_H_

#define CORGI_MEMORY_H_

typedef struct _MEMORY {
	u32 address_space;
	u32 *memory;
	bool write;
} MEMORY;

MEMORY * memory_init(u32 address_space, bool read_only);
void memory_free(MEMORY *memory);
u32 memory_update(MEMORY *memory, u32 address, u32 data);

#endif