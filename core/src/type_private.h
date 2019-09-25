#ifndef ILR_TYPE_PRIVATE_H
#define ILR_TYPE_PRIVATE_H

#include "ilr/type.h"

#include "ilr_private.h"

struct ilr_value_type_ {
  ilr_element_t * type;
  unsigned size;
};

/// Get the expected # of elements for type by reading the head of the array
unsigned ilr_type_get_unboxed_size(ilr_element_t * tarr, unsigned tarr_size);

#endif // ILR_TYPE_PRIVATE_H
