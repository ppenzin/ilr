#include "ilr/Type.h"

using namespace ilr;

Type::Type(void) {};

Type * Type::CreateVoidType() {
  return new Type(ilr_type_void());
}

Type * Type::CreateFloatType() {
  return new Type(ilr_type_float());
}

Type * Type::CreateDoubleType() {
  return new Type(ilr_type_double());
}

Type * Type::CreatePointerType(Type * pointee) {
  return new Type(ilr_type_pointer(pointee->core_type));
}

Type::~Type() {
  ilr_type_free(&core_type);
}
