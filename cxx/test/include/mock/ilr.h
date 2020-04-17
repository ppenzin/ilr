/// \file ilr.h mockup type for ilr C library

#ifndef MOCK_ILR_H
#define MOCK_ILR_H

#include "mock/snapshot.h"

/// Type to coordinate mocking up the C library
namespace mock {
  class ilr_mock_t : public Snapshot<ilr_mock_t> {
  };
} // mock

#endif // MOCK_ILR_H
