#ifndef TYPE_H
#define TYPE_H

#include "ilr/type.h"

namespace ilr {

/// Representation of a ILR value type
class Type {
private:
  ilr_value_type_t * core_type;

  /// Default constructor is hidden to disable creation of "unknown" types
  Type();

public:

  Type(ilr_value_type_t * t) : core_type(t) {}

  // TODO Type(Type& M)
  // TODO Type(Type&& M)

  ~Type();

  /// Create a void type
  static Type * CreateVoidType();
  /// Create a float type
  static Type * CreateFloatType();
  /// Create a double type
  static Type * CreateDoubleType();
  /// Create a pointer type
  static Type * CreatePointerType(Type * pointee);
};

} // namespace ilr

#endif // TYPE_H
