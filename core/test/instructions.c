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

  /***** Checks *****/

  i.size = 1;
  i.instr = malloc(sizeof(ilr_element_t) * i.size);
  i.instr[0] = ilr_nop;
  CHECK(ilr_instruction_is(&i) == ilr_nop);

  free(i.instr);
}

