#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

#define ADDRESS_SPACE 0xFFFF

MEMORY *memory;

/**
 * Initialize the simulator.
 */
void sim_init() {
	memory = memory_init(ADDRESS_SPACE);
}

/**
 * Free all allocated memory space.
 */
void sim_free() {
	memory_free(memory);
}

/**
 * Main body of the program.
 *
 * @param argc Number of arguments from the command line.
 * @param arg Array of strings containing the command line arguments.
 * @return Either EXIT_SUCCESS or EXIT_FAILURE
 */ 
int main(int argc, char **argv) {
	sim_init();

	sim_free();

	return EXIT_SUCCESS;
}