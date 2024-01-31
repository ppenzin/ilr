#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "instruction_private.h"

enum ilr_opcode ilr_instruction_is(ilr_instruction_t * i) {
  assert(i->instr);

  return i->instr[0];
}

/// Allocate instruction array section and fill in the opcode
/// \param ins the instruction to initalize
/// \param op the opcode
/// \param size number of elements to reserve
void ilr_instruction_init(ilr_instruction_t * ins, enum ilr_opcode op, unsigned size) {
  ins->size = size;
  ins->instr = malloc(sizeof(ilr_element_t) * ins->size);
  ins->instr[0] = op;
}

ilr_instruction_t * ilr_instruction_nop(void) {
  ilr_instruction_t * ins = malloc(sizeof(ilr_instruction_t));
  ilr_instruction_init(ins, ilr_nop, 1);
  return ins;
}

// FIXME should the field indicating size be number of words or number of instructions?
ilr_block_t * ilr_instruction_block(void) {
  ilr_block_t * b = malloc(sizeof(ilr_block_t));
  ilr_instruction_init(&(b->code), ilr_block, 2);
  b->code.instr[1] = 0; // Number of instructions following the entry point
  return b;
}

void ilr_block_append(ilr_block_t * block, ilr_instruction_t * instruction) {
  assert(block->code.instr);
  assert(block->code.instr[0] == ilr_block);

  // Add space for the instruction
  block->code.instr = realloc(block->code.instr,
    sizeof(ilr_element_t) * (block->code.size + instruction->size));
  // Add the instruction
  memcpy(block->code.instr + block->code.size, instruction->instr,
    sizeof(ilr_element_t) * instruction->size);
  // Increment block size
  block->code.size += instruction->size;
  block->code.instr[1]++;
}

void ilr_instruction_free(ilr_instruction_t ** i) {
  free ((*i)->instr);
  free (*i);
  *i = NULL;
}

void ilr_block_free(ilr_block_t ** b) {
  free ((*b)->code.instr);
  free (*b);
  *b = NULL;
}
