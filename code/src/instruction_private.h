#ifndef ILR_INSTRUCTION_PRIVATE_H
#define ILR_INSTRUCTION_PRIVATE_H

#include "ilr/instruction.h"

#include "ilr_private.h"

struct ilr_instruction_ {
  ilr_element_t * instr;
  unsigned size;
};

struct ilr_block_ {
  // Instructions of the block get allocated inside of this
  ilr_instruction_t code;
};


#endif // ILR_INSTRUCTION_PRIVATE_H
