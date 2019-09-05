#include "ilr/module.h"

#include "mock/module.h"

struct stat_t {
  unsigned ilr_new_module;
  unsigned ilr_free_module;
  stat_t() : ilr_new_module(0), ilr_free_module(0) {}
};

static stat_t stats;

extern "C" {

ilr_module_t * ilr_new_module(void) {
  ++stats.ilr_new_module;
  return nullptr;
}

void ilr_free_module(ilr_module_t ** module) {
  ++stats.ilr_free_module;
}

}

unsigned mock::module::called_ilr_new_module(void) {
  return stats.ilr_new_module;
}

unsigned mock::module::called_ilr_free_module(void) {
  return stats.ilr_free_module;
}
