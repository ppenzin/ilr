#ifndef MOCK_MODULE_H
#define MOCK_MODULE_H

#include "mock/ilr.h"
#include "mock/snapshot.h"

namespace mock {
namespace module {
  Snapshot<ilr_mock_t> &ilr_new_module();
  Snapshot<ilr_mock_t> &ilr_free_module();
} // module
} // mock

#endif // MOCK_MODULE_H
