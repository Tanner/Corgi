#include <stdbool.h>

#include "types.h"
#include "memory.h"

#ifndef CORGI_MICROCONTROLLER_H_

#define CORGI_MICROCONTROLLER_H_

/**
 * Content of the microcontroller main ROM contains the next state in bits 0-5.
 */
#define MICROCONTROLLER_NEXT_STATE(CONTENTS) ((CONTENTS) & 0x1F)

/**
 * Content is located at the bits specified in the main rom.
 */
#define MICROCONTROLLER_DR_REG 6
#define MICROCONTROLLER_DR_MEM 7
#define MICROCONTROLLER_DR_ALU 8
#define MICROCONTROLLER_DR_PC 9
#define MICROCONTROLLER_DR_OFF 10
#define MICROCONTROLLER_LD_PC 11
#define MICROCONTROLLER_LD_IR 12
#define MICROCONTROLLER_LD_MAR 13
#define MICROCONTROLLER_LD_A 14
#define MICROCONTROLLER_LD_B 15
#define MICROCONTROLLER_LD_Z 16
#define MICROCONTROLLER_WR_REG 17
#define MICROCONTROLLER_WR_MEM 18
#define MICROCONTROLLER_REG_SEL_LO 19
#define MICROCONTROLLER_REG_SEL_HI 20
#define MICROCONTROLLER_ALU_LO 21
#define MICROCONTROLLER_ALU_HI 22
#define MICROCONTROLLER_OP_TEST 23
#define MICROCONTROLLER_CHK_Z 24

/**
 * Select register field bit locations.
 */
#define MICROCONTROLLER_RX 0
#define MICROCONTROLLER_RY 1
#define MICROCONTROLLER_RZ 2

/**
 * Retrievies the bit in the first position in a bitstring after shifting an
 * amount. 
 */
#define MICROCONTROLLER_RETRIEVE_BIT(CONTENTS, SHIFT) ((CONTENTS) >> SHIFT & 0x1)

typedef struct _MICROCONTROLLER {
	MEMORY *main;
	MEMORY *sequencer;
	MEMORY *onZ;
	MEMORY *state;
} MICROCONTROLLER;

MICROCONTROLLER * microcontroller_init();
void microcontroller_free(MICROCONTROLLER *microcontroller);
u32 microcontroller_update(MICROCONTROLLER *microcontroller, u8 opcode, bool z);

#endif