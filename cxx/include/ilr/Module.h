#ifndef MODULE_H
#define MODULE_H

#include "ilr/module.h"

namespace ilr {

/// Representation of a (sub)program
class Module {
private:
  ilr_module_t * core_module;
public:
  Module();

  Module(ilr_module_t * m) : core_module(m) {}

  // TODO Module(Module& M)
  // TODO Module(Module&& M)

  ~Module();
};

} // namespace ilr

#endif // MODULE_H
