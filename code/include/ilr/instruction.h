/// \file instruction.h
/// Describes ILR intermediate representation instructions

#ifndef ILR_INSTRUCTION_H
#define ILR_INSTRUCTION_H

#ifdef __cplusplus
extern "C" {
#endif

/// IR instruction
typedef struct ilr_instruction_ ilr_instruction_t;
/// Basic block
typedef struct ilr_block_ ilr_block_t;

/// Operations
enum ilr_opcode {
  /// NOP
  ilr_nop = 0,
  /// Basic block entry
  ilr_block,
};

/// Check the opcode
enum ilr_opcode ilr_instruction_is(ilr_instruction_t * i);

// Creation of instructions

/// Get a NOP
ilr_instruction_t * ilr_instruction_nop(void);

/// Get a block
ilr_block_t * ilr_instruction_block(void);

/// Add an instruction to the end of a basic block
/// FIXME block type
void ilr_block_append(ilr_block_t * block, ilr_instruction_t * instruction);

/// Free instruction
void ilr_instruction_free(ilr_instruction_t ** i);

/// Free block 
void ilr_block_free(ilr_block_t ** i);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ILR_INSTRUCTION_H
