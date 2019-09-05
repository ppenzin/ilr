#include "ilr/Module.h"

using namespace ilr;

Module::Module(void) {
  core_module = ilr_new_module();
}

Module::~Module() {
  ilr_free_module(&core_module);
}
