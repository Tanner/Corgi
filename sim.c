#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "sim.h"
#include "memory.h"
#include "alu.h"

#define ADDRESS_SPACE 0xFFFF

#define REGISTERS_COUNT 8

void * sim_pc();
void * sim_ir();
void * sim_alu();
void * sim_registers();
void * sim_memory();
void * sim_z();

static bool sim_running;

static MEMORY *memory;
static MEMORY *registers;
static MEMORY *pc;
static MEMORY *ir;
static MEMORY *mar;
static MEMORY *z;

static MEMORY *a;
static MEMORY *b;

static u32 bus;
static pthread_mutex_t bus_mutex;

static ALU_FUNCTION alu_function;
static u32 register_number;

static bool dr_pc;
static bool dr_alu;
static bool dr_reg;
static bool dr_mem;

static pthread_t pc_thread;
static pthread_t ir_thread;
static pthread_t alu_thread;
static pthread_t registers_thread;
static pthread_t memory_thread;
static pthread_t z_thread;

/**
 * Initialize the simulator.
 */
void sim_init() {
	memory = memory_init(ADDRESS_SPACE);
	registers = memory_init(REGISTERS_COUNT);
	pc = memory_init(1);
	ir = memory_init(1);
	mar = memory_init(1);
	z = memory_init(1);

	a = memory_init(1);
	b = memory_init(1);

	pthread_mutex_init(&bus_mutex, NULL);

	sim_running = true;

	pthread_create(&pc_thread, NULL, sim_pc, NULL);
	pthread_create(&ir_thread, NULL, sim_ir, NULL);
	pthread_create(&alu_thread, NULL, sim_alu, NULL);
	pthread_create(&registers_thread, NULL, sim_registers, NULL);
	pthread_create(&memory_thread, NULL, sim_memory, NULL);
	pthread_create(&z_thread, NULL, sim_z, NULL);
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
 * Thread simulating the actions of the instruction register.
 */
void * sim_ir() {
	while (sim_running) {
		pthread_mutex_lock(&bus_mutex);

		memory_update(ir, 0, bus);

		pthread_mutex_unlock(&bus_mutex);
	}

	return NULL;
}

/**
 * Thread simulating the actions of the ALU and both a/b temporary registers.
 */
void * sim_alu() {
	while (sim_running) {
		pthread_mutex_lock(&bus_mutex);

		memory_update(a, 0, bus);
		memory_update(b, 0, bus);

		pthread_mutex_unlock(&bus_mutex);

		u32 alu_result = alu_update(alu_function, a->memory[0], b->memory[0]);

		sim_tristate_buffer(alu_result, dr_alu);
	}

	return NULL;
}

/**
 * Thread simulating the actions of the register file.
 */
void * sim_registers() {
	while (sim_running) {
		pthread_mutex_lock(&bus_mutex);

		u32 value = memory_update(registers, register_number, bus);

		pthread_mutex_unlock(&bus_mutex);

		sim_tristate_buffer(value, dr_reg);
	}

	return NULL;
}

/**
 * Thread simulating the actions of the memory.
 */
void * sim_memory() {
	while (sim_running) {
		pthread_mutex_lock(&bus_mutex);

		u32 address = memory_update(memory, 0, bus);

		u32 value = memory_update(memory, address, bus);

		pthread_mutex_unlock(&bus_mutex);

		sim_tristate_buffer(value, dr_mem);
	}

	return NULL;
}

/**
 * Thread simulating the actions of the Z register.
 */
void * sim_z() {
	while (sim_running) {
		pthread_mutex_lock(&bus_mutex);

		bool is_zero = bus == 0 ? false : true;

		memory_update(z, 0, is_zero);

		pthread_mutex_unlock(&bus_mutex);
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

	pthread_join(pc_thread, NULL);
	pthread_join(ir_thread, NULL);
	pthread_join(alu_thread, NULL);
	pthread_join(registers_thread, NULL);
	pthread_join(memory_thread, NULL);
	pthread_join(z_thread, NULL);
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
	memory_free(z);

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