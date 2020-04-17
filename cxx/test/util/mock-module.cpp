#include "ilr/module.h"

#include "mock/module.h"

using namespace mock;

namespace stats {
  static SnapshotWriter<ilr_mock_t> ilr_new_module;
  static SnapshotWriter<ilr_mock_t> ilr_free_module;
}

extern "C" {

ilr_module_t * ilr_new_module(void) {
  stats::ilr_new_module.set();
  return nullptr;
}

void ilr_free_module(ilr_module_t ** module) {
  stats::ilr_free_module.set();
}

}

Snapshot<ilr_mock_t> &module::ilr_new_module() {
  return stats::ilr_new_module;
}

Snapshot<ilr_mock_t> &module::ilr_free_module() {
  return stats::ilr_free_module;
}
