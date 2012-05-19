#include "types.h"

#ifndef CORGI_ALU_H_

#define CORGI_ALU_H_

typedef enum _ALU_FUNCTION { ADD, NAND, SUBTRACT, A_PLUS_ONE } ALU_FUNCTION;

u32 alu_update(ALU_FUNCTION function, u32 a, u32 b);

#endif