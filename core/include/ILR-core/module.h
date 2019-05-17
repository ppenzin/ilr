#ifndef ILR_MODULE_H
#define ILR_MODULE_H

#include "ILR-core/instructions.h"

#include <stddef.h>

struct module {
  size_t instructions_size;
  ilr_t * instructions;
};

#endif // ILR_MODULE_H
