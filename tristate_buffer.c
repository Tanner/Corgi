#include <stdbool.h>

#include "tristate_buffer.h"

/**
 * Return input if enable is true and 0 is false.
 * 
 * @param input Input into the tristate buffer
 * @param enable Whether or not to continue sending the input
 */
u32 tristate_buffer_update(u32 input, bool enable) {
	if (enable) {
		return input;
	}

	return 0;
}