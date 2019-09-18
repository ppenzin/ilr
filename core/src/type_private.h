#ifndef ILR_TYPE_PRIVATE_H
#define ILR_TYPE_PRIVATE_H

#include "ilr/type.h"

#include "ilr_private.h"

struct ilr_value_type_ {
  ilr_element_t * type;
};

/// Number of arguments to the type
unsigned get_type_num_args(enum ilr_type t);

#endif // ILR_TYPE_PRIVATE_H
