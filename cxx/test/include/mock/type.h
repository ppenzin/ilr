#ifndef MOCK_TYPE_H
#define MOCK_TYPE_H

#include "mock/ilr.h"
#include "mock/snapshot.h"

namespace mock {
namespace type {
  Snapshot<ilr_mock_t>&ilr_type_free();
  Snapshot<ilr_mock_t>&ilr_type_void();
  Snapshot<ilr_mock_t>&ilr_type_float();
  Snapshot<ilr_mock_t>&ilr_type_double();
  Snapshot<ilr_mock_t>&ilr_type_pointer();
} // module
} // mock

#endif // MOCK_TYPE_H
