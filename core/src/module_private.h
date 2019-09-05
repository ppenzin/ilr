#ifndef ILR_MODULE_PRIVATE_H
#define ILR_MODULE_PRIVATE_H

#include "ilr/module.h"

/// IR is an array
typedef unsigned short ilr_element_t;

struct ilr_module_ {
  ilr_element_t * module;
  unsigned size;
};

#endif // ILR_MODULE_PRIVATE_H

