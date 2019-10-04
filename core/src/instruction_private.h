#ifndef ILR_INSTRUCTION_PRIVATE_H
#define ILR_INSTRUCTION_PRIVATE_H

#include "ilr/instruction.h"

#include "ilr_private.h"

struct ilr_instruction_ {
  ilr_element_t * instr;
  unsigned size;
};

#endif // ILR_INSTRUCTION_PRIVATE_H
