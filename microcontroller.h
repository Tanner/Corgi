#include <stdbool.h>

#include "types.h"
#include "memory.h"

#ifndef CORGI_MICROCONTROLLER_H_

#define CORGI_MICROCONTROLLER_H_

typedef struct _MICROCONTROLLER {
	MEMORY *main;
	MEMORY *sequencer;
	MEMORY *onZ;
	MEMORY *state;
} MICROCONTROLLER;

MICROCONTROLLER * microcontroller_init();
void microcontroller_free(MICROCONTROLLER *microcontroller);
void microcontroller_update(MICROCONTROLLER *microcontroller, u8 opcode, bool z);

#endif