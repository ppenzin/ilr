#include "ilr/Module.h"

#include "test/verify.h"
#include "mock/module.h"

using namespace ilr;

int main() {
  // Verify that the wrapper calls allocation and deallocation routines
  Module * m = new Module();
  delete m;

  test::verify(mock::module::ilr_new_module().getNumCalls(), (unsigned)1);
  test::verify(mock::module::ilr_free_module().getNumCalls(), (unsigned)1);

  return test::report();
}
