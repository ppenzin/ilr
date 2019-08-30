#ifndef INSTRUCTION_H
#define INSTRUCTION_H

extern "C" {
#include "ILR-core/instructions.h"
}

namespace ILR {

class Instruction;
class Module;

/// Value from an instruction, static, type, etc
enum ArgumentType {
  Value
};

// FIXME create a separate instance class that would hold, module, entity type and index?

/// Instruction argument
template<ArgumentType T>
class Argument {
  private:
  ArgumentType Ty = T;
  /// Module that this arguments belong in
  Module * module;
  /// Index (into whichever array is appropriate for it)
  ilr_t index;
  public:
  ArgumentType getType() { return Ty; }
};

class ValueArgument : public Argument<Value> {
  public:
  ValueArgument(Instruction &src);
};

// TODO Instruction class, template on opcode?
template <op Opcode>
class Instructon {
  private:
  op Op = Opcode;
  /// Module that this arguments belong in
  Module * module;
  /// Index into instruction array
  ilr_t index;
  
  public:
  static const unsigned NArgs;

  op getOpcode() const {
    return Op;
  }
};

} // namespace ILR


#endif // INSTRUCTION_H

