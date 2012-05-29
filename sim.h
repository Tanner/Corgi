#include <stdbool.h>

#include "types.h"

#ifndef CORGI_SIM_H_

#define CORGI_SIM_H_

#define BITS_15_to_13(A) ((A) >> 12 & 0x7)
#define BITS_12_to_9(A) (((A) >> 8) & 0xF)
#define BITS_8_to_5(A) (((A) >> 4) & 0xF)
#define BITS_4_to_0(A) ((A) & 0x1F)
#define BITS_3_to_0(A) ((A) & 0xF)

void sim_tristate_buffer(u32 input, bool enable);

#endif