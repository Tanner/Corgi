#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

#define ADDRESS_SPACE 0xFFFF

#define REGISTERS_COUNT 8

static MEMORY *memory;
static MEMORY *registers;
static MEMORY *pc;
static MEMORY *ir;
static MEMORY *mar;

static MEMORY *a;
static MEMORY *b;

u32 bus;

/**
 * Initialize the simulator.
 */
void sim_init() {
	memory = memory_init(ADDRESS_SPACE);
	registers = memory_init(REGISTERS_COUNT);
	pc = memory_init(1);
	ir = memory_init(1);
	mar = memory_init(1);

	a = memory_init(1);
	b = memory_init(1);
}

/**
 * Free all allocated memory space.
 */
void sim_free() {
	memory_free(memory);
	memory_free(registers);
	memory_free(pc);
	memory_free(ir);
	memory_free(mar);

	memory_free(a);
	memory_free(b);
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