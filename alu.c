#include "alu.h"
#include "types.h"

/**
 * Perform an ALU_FUNCTION given two inputs.
 * 
 * @param function ALU_FUNCTION to perform on a and b
 * @param a First input
 * @param b Second input
 * @return Result of ALU_FUNCTION on a and b
 */
u32 alu_update(ALU_FUNCTION function, u32 a, u32 b) {
	switch (function) {
		case ADD:
			return a + b;
			break;
		case NAND:
			return ~(a & b);
			break;
		case SUBTRACT:
			return a - b;
			break;
		case A_PLUS_ONE:
			return a + 1;
			break;
	}

	return 0;
}