#include <stdlib.h>
#include <assert.h>

#include "memory.h"
#include "types.h"

/**
 * Allocate MEMORY and allocate space for its memory according to the given
 * address space size.
 *
 * @param address_space Address space for the memory
 * @return MEMORY pointer
 */
MEMORY * memory_init(u32 address_space) {
	int i;

	MEMORY *newMemory = malloc(sizeof(MEMORY));
	assert(newMemory);

	newMemory->address_space = address_space;

	newMemory->memory = malloc(sizeof(u32) * address_space);
	assert(newMemory->memory);

	for (i = 0; i < address_space; i++) {
		newMemory->memory[i] = 0;
	}

	return newMemory;
}

void memory_free(MEMORY *memory) {
	free(memory->memory);

	free(memory);
}