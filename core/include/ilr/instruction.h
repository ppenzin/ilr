/// \file instruction.h
/// Describes ILR intermediate representation instructions

#ifndef ILR_INSTRUCTION_H
#define ILR_INSTRUCTION_H

#ifdef __cplusplus
extern "C" {
#endif

/// IR instruction
typedef struct ilr_instruction_ ilr_instruction_t;

/// Operations
enum ilr_opcode {
  /// NOP
  ilr_nop = 0,
};

/// Check the opcode
enum ilr_opcode ilr_instruction_is(ilr_instruction_t * i);

// Creation of instructions

/// Get a NOP
ilr_instruction_t * ilr_instruction_nop(void);

/// Free instruction
void ilr_instruction_free(ilr_instruction_t ** i);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ILR_INSTRUCTION_H
