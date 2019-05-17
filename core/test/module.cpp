#include "ILR/Module.h"

#include "test/verify.h"

using namespace ILR;

int main() {
  std::unique_ptr<Module> m(new Module());

  test::verify(m.get()->get_module()->instructions_size, (size_t)0);
  test::verify(m.get()->get_module()->instructions, (unsigned short*)nullptr);

  module * mod = m.get()->release_module();

  std::unique_ptr<Module> m2(new Module(mod));

  test::verify(m2.get()->get_module(), (const module *)mod);

  return test::report();
}
