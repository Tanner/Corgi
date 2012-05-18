#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

#define ADDRESS_SPACE 0xFFFF

/**
 * Initialize the simulator.
 */
void sim_init() {
	MEMORY *memory = memory_init(ADDRESS_SPACE);
	free(memory);
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

	return EXIT_SUCCESS;
}