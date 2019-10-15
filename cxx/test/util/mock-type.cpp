#include "ilr/type.h"

#include "mock/type.h"

using namespace mock;

namespace stats {
  SnapshotWriter<ilr_mock_t> ilr_type_void;
  SnapshotWriter<ilr_mock_t> ilr_type_float;
  SnapshotWriter<ilr_mock_t> ilr_type_double;
  SnapshotWriter<ilr_mock_t> ilr_type_pointer;
  SnapshotWriter<ilr_mock_t> ilr_type_free;
}

extern "C" {

ilr_value_type_t * ilr_type_void(void) {
  stats::ilr_type_void.set();
  return nullptr;
}

ilr_value_type_t * ilr_type_float(void) {
  stats::ilr_type_float.set();
  return nullptr;
}

ilr_value_type_t * ilr_type_double(void) {
  stats::ilr_type_double.set();
  return nullptr;
}

ilr_value_type_t * ilr_type_pointer(ilr_value_type_t * pointee) {
  stats::ilr_type_pointer.set();
  return nullptr;
}

void ilr_type_free(ilr_value_type_t ** type) {
  stats::ilr_type_free.set();
}

}

Snapshot<ilr_mock_t> &mock::type::ilr_type_free(void) {
  return stats::ilr_type_free;
}

Snapshot<ilr_mock_t> &mock::type::ilr_type_void(void) {
  return stats::ilr_type_void;
}

Snapshot<ilr_mock_t> &mock::type::ilr_type_float(void) {
  return stats::ilr_type_float;
}

Snapshot<ilr_mock_t> &mock::type::ilr_type_double(void) {
  return stats::ilr_type_double;
}

Snapshot<ilr_mock_t> &mock::type::ilr_type_pointer(void) {
  return stats::ilr_type_pointer;
}
