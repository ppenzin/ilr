/// \filr instructions.c Test instructions manipulations

#include <stdbool.h>
#include <stdlib.h>

#include "check.h"
#include "instruction_private.h"

int main(void) {
  ilr_instruction_t * p;
  ilr_instruction_t i;

  /***** Initialization *****/

  p = ilr_instruction_nop();
  CHECK(p->size == 1);
  CHECK(p->instr[0] == ilr_nop);
  ilr_instruction_free(&p);
  CHECK(p == NULL);

  ilr_block_t * b = ilr_instruction_block();
  CHECK(b->code.size == 2);
  CHECK(b->code.instr[0] == ilr_block);
  CHECK(b->code.instr[1] == 0);
  // Append
  p = ilr_instruction_nop();
  ilr_block_append(b, p);
  CHECK(b->code.size == 3);
  CHECK(b->code.instr[0] == ilr_block);
  CHECK(b->code.instr[1] == 1);
  CHECK(b->code.instr[2] == ilr_nop);
  ilr_block_append(b, p);
  CHECK(b->code.size == 4);
  CHECK(b->code.instr[0] == ilr_block);
  CHECK(b->code.instr[1] == 2);
  CHECK(b->code.instr[2] == ilr_nop);
  CHECK(b->code.instr[3] == ilr_nop);
  //Free
  ilr_block_free(&b);
  CHECK(b == NULL);
  ilr_instruction_free(&p);
  CHECK(p == NULL);

  /***** Checks *****/

  i.size = 1;
  i.instr = malloc(sizeof(ilr_element_t) * i.size);
  i.instr[0] = ilr_nop;
  CHECK(ilr_instruction_is(&i) == ilr_nop);

  i.size = 3;
  i.instr = malloc(sizeof(ilr_element_t) * i.size);
  i.instr[0] = ilr_block;
  i.instr[1] = 3;
  i.instr[2] = ilr_nop;
  CHECK(ilr_instruction_is(&i) == ilr_block);

  free(i.instr);

  return check_report();
}

