#ifndef MODULE_H
#define MODULE_H

#include <memory>

extern "C" {
#include "ILR-core/module.h"
}

namespace ILR {

class Module;

/// Parts of the module, also things that instructions can reference
enum ReferenceType {
  Instruction
};

// TODO consistency enforcement. Saving index is not a guarantee as data can
// change under that index. Probably a better way is to save the pointer and a
// checksum for the data.

/// Refer to an entity inside of a module
template <ReferenceType T>
class Reference {
  private:
  Module * module;
  ReferenceType type = T;
  ilr_t index;
  Reference<T> (); // No default constructor
  public:
  Reference<T> (Module * mod, ilr_t ind) : module(mod), index(ind) {}
};

/// Representation of a (sub)program
class Module {
private:
  std::unique_ptr<struct module> core_module;
public:
  Module() : core_module(new module) {
    core_module->instructions_size = 0;
    core_module->instructions = nullptr;
  }

  Module(module * m) : core_module(m) {}

  // TODO Module(Module& M)
  // TODO Module(Module&& M)

  const module * get_module() const {
    return core_module.get();
  }

  module * release_module() {
    return core_module.release();
  }
};

} // namespace ILR

#endif // MODULE_H
