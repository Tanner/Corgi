#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "memory.h"

#define ADDRESS_SPACE 0xFFFF

#define REGISTERS_COUNT 8

void sim_tristate_buffer(u32 input, bool enable);

void * sim_pc();

static bool sim_running;

static MEMORY *memory;
static MEMORY *registers;
static MEMORY *pc;
static MEMORY *ir;
static MEMORY *mar;

static MEMORY *a;
static MEMORY *b;

static u32 bus;
static pthread_mutex_t bus_mutex;

static bool dr_pc;

static pthread_t pc_thread;

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

	pthread_mutex_init(&bus_mutex, NULL);

	sim_running = true;

	pthread_create(&pc_thread, NULL, sim_pc, NULL);
}

/**
 * Thread simulating the actions of the program counter and its tristate buffer.
 */
void * sim_pc() {
	while (sim_running) {
		pthread_mutex_lock(&bus_mutex);

		u32 pc_value = memory_update(pc, 0, bus);

		pthread_mutex_unlock(&bus_mutex);

		sim_tristate_buffer(pc_value, dr_pc);
	}

	return NULL;
}

/**
 * Simulator a tristate buffer that is connected to the bus.
 * 
 * @param input Input is sent to the bus is enable is true
 * @param enable Whether or not input is sent to the bus
 */
void sim_tristate_buffer(u32 input, bool enable) {
	if (!enable) {
		return;
	}

	pthread_mutex_lock(&bus_mutex);

	bus = input;

	pthread_mutex_unlock(&bus_mutex);
}

/**
 * Prepare the simulator to be deallocated. Set the simulator to not be running
 * and destroy all pthreads.
 */
void sim_destroy() {
	sim_running = false;

	pthread_mutex_destroy(&bus_mutex);
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

	sim_destroy();
	sim_free();

	pthread_exit(NULL);

	return EXIT_SUCCESS;
}