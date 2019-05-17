#ifndef MODULE_H
#define MODULE_H

#include <memory>

extern "C" {
#include "ILR-core/module.h"
}

namespace ILR {

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
