#ifndef ILR_INSTRUCTIONS_H
#define ILR_INSTRUCTIONS_H

// Instruction array entry
typedef unsigned short ilr_t;

enum op {
  // TODO start index
  IADD,
  FADD,
};

/// Add a new entry to array of instructions
void add_operation(ilr_t * dest, op, ilr_t * args, unsigned n_args); 

#endif // ILR_INSTRUCTIONS_H
