#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#include "type_private.h"

enum ilr_type ilr_type_is(ilr_value_type_t * t) {
  assert(t->type);

  return t->type[0];
}

ilr_value_type_t * ilr_type_new(enum ilr_type kind, ...) {
  unsigned i, num_args = get_type_num_args(kind);

  // Allocate type struct and its internal array
  ilr_value_type_t * t = malloc(sizeof(ilr_value_type_t));
  t->type = malloc(sizeof(ilr_element_t) * (num_args + 1));

  // Type ID goes into the first slot
  t->type[0] = kind;

  // The rest gets filled by the parameters
  va_list args;
  va_start(args, kind);
  for (i = 0; i < num_args; ++i) {
    // FIXME complex types
    t->type[i+1] = va_arg(args, int);
  }
  va_end(args);

  return t;
}

void ilr_type_free(ilr_value_type_t ** t) {
  free((*t)->type);
  free(*t);
  t = NULL;
}

unsigned ilr_get_int_width(ilr_value_type_t * t) {
  assert(t->type[0] == ilr_int);
  return t->type[1];
}

unsigned get_type_num_args(enum ilr_type t) {
  switch (t) {
    case ilr_void:
    case ilr_float:
    case ilr_double:
      return 0;
    case ilr_int:
    case ilr_pointer:
      return 1;
    default:
      // FIXME struct and func
      assert(0);
  }
}

