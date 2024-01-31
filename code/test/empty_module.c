/* Test module allocation and deallocation */
#include "ilr/module.h"

int main(void) {
  ilr_module_t * module = ilr_new_module();
  ilr_free_module(&module);
  return 0;
}

