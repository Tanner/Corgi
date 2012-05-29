#include <stdlib.h>
#include <assert.h>

#include "microcontroller.h"
#include "memory.h"

#define MAIN_ROM_ADDRESS_SPACE 64 /* 2^6 */
#define SEQUENCER_ROM_ADDRESS_SPACE 8 /* 2^3 */
#define ON_Z_ROM_ADDRESS_SPACE 2

#define STATE_REGISTER_ADDRESS_SPACE 1

/**
 * Allocate MICRO_CONTROLLER and allocate space for its members.
 *
 * @return MICROCONTROLLER pointer
 */
MICROCONTROLLER * microcontroller_init() {
	MICROCONTROLLER *newMicrocontroller = malloc(sizeof(MICROCONTROLLER));
	assert(newMicrocontroller);

	newMicrocontroller->main = memory_init(MAIN_ROM_ADDRESS_SPACE, true);
	newMicrocontroller->sequencer = memory_init(SEQUENCER_ROM_ADDRESS_SPACE, true);
	newMicrocontroller->onZ = memory_init(ON_Z_ROM_ADDRESS_SPACE, true);

	newMicrocontroller->state = memory_init(STATE_REGISTER_ADDRESS_SPACE, false);

	return newMicrocontroller;
}

/**
 * Free a MICROCONTROLLER.
 * 
 * @param microcontroller Pointer to a MICROCONTROLLER
 */
void microcontroller_free(MICROCONTROLLER *microcontroller) {
	free(microcontroller->main);
	free(microcontroller->sequencer);
	free(microcontroller->onZ);

	free(microcontroller->state);

	free(microcontroller);
}

u32 microcontroller_update(MICROCONTROLLER *microcontroller, u8 opcode, bool z) {
	u32 stateContents = memory_read(microcontroller->main, memory_read(microcontroller->state, 0));

	return stateContents;
}