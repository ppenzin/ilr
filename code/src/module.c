#include <stdlib.h>

#include "module_private.h"

ilr_module_t * ilr_new_module(void) {
  ilr_module_t * module = malloc(sizeof(ilr_module_t));
  module->module = NULL;
  module->size = 0;
  return module;
}

void ilr_free_module(ilr_module_t ** module) {
  if ((*module)->size) {
    free((*module)->module);
    (*module)->module = NULL;
    (*module)->size = 0;
  }

  free(*module);
  *module = NULL;
}
