#include "ilr/Type.h"

#include "test/verify.h"
#include "mock/type.h"

using namespace ilr;

int main() {
  // Verify that the wrapper calls allocation and deallocation routines
  Type * t = Type::CreateVoidType();
  test::verify(mock::type::ilr_type_void().getNumCalls(), (unsigned)1);
  delete t;
  test::verify(mock::type::ilr_type_free().getNumCalls(), (unsigned)1);

  t = Type::CreateFloatType();
  test::verify(mock::type::ilr_type_float().getNumCalls(), (unsigned)1);
  delete t;
  test::verify(mock::type::ilr_type_free().getNumCalls(), (unsigned)2);

  t = Type::CreateDoubleType();
  test::verify(mock::type::ilr_type_double().getNumCalls(), (unsigned)1);
  delete t;
  test::verify(mock::type::ilr_type_free().getNumCalls(), (unsigned)3);

  return test::report();
}
