#include <assert.h>
#include <stdlib.h>

#include "instruction_private.h"

enum ilr_opcode ilr_instruction_is(ilr_instruction_t * i) {
  assert(i->instr);

  return i->instr[0];
}

/// Allocate instruction array section and fill in the opcode
/// \param op the opcode
/// \param size number of elements to reserve
ilr_instruction_t * ilr_instruction_init(enum ilr_opcode op, unsigned size) {
  ilr_instruction_t * ins = malloc(sizeof(ilr_instruction_t));
  ins->size = size;
  ins->instr = malloc(sizeof(ilr_element_t) * ins->size);
  ins->instr[0] = op;
  return ins;
}

ilr_instruction_t * ilr_instruction_nop(void) {
  return ilr_instruction_init(ilr_nop, 1);
}

void ilr_instruction_free(ilr_instruction_t ** i) {
  free ((*i)->instr);
  free (*i);
  *i = NULL;
}
