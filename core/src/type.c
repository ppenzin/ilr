#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "type_private.h"

unsigned ilr_type_get_unboxed_size(ilr_element_t * tarr, unsigned tarr_size) {
  enum ilr_type kind = tarr[0];
  unsigned size, entry_size, num_entries, i;
  switch(kind) {
    case ilr_void:
    case ilr_float:
    case ilr_double:
      assert(tarr_size > 0);
      return 1;
    case ilr_int:
      assert(tarr_size > 1);
      return 2;
    case ilr_pointer:
      assert(tarr_size > 1);
      return (ilr_type_get_unboxed_size(tarr + 1, tarr_size - 1) + 1);
    case ilr_array:
    case ilr_vector:
      assert(tarr_size > 2);
      return (ilr_type_get_unboxed_size(tarr + 2, tarr_size - 2) + 2);
    case ilr_struct:
      assert(tarr_size > 2);
      num_entries = tarr[1];
      size = 2;
      tarr += 2;
      tarr_size -= 2;
      for (i = 0; i < num_entries; ++i) {
        entry_size = ilr_type_get_unboxed_size(tarr, tarr_size);
        size += entry_size;
        tarr += entry_size;
        tarr_size -= entry_size;
      }
      return size;
    case ilr_func:
      assert(tarr_size > 2);
      size = 2;
      num_entries = tarr[1] + 1; // Number of arguments + one more for return type
      tarr +=2;
      tarr_size -= 2;
      for (i = 0; i < num_entries; ++ i) {
        entry_size = ilr_type_get_unboxed_size(tarr, tarr_size);
        size += entry_size;
        tarr += entry_size;
        tarr_size -= entry_size;
      }
      return size;
    default:
      assert(0);
  }
}

enum ilr_type ilr_type_is(ilr_value_type_t * t) {
  assert(t->type);

  return t->type[0];
}

/// Allocate type array and fill in the first element
/// \param kind type of the value
/// \param size number of elements in type array
ilr_value_type_t * ilr_type_init(enum ilr_type kind, unsigned size) {
  ilr_value_type_t * t = malloc(sizeof(ilr_value_type_t));
  t->size = size;
  t->type = malloc(sizeof(ilr_element_t) * t->size);
  t->type[0] = kind;
  return t;
}

// TODO types without vaiability can be statically allocated

ilr_value_type_t * ilr_type_void(void) {
  return ilr_type_init(ilr_void, 1);
}

ilr_value_type_t * ilr_type_float(void) {
  return ilr_type_init(ilr_float, 1);
}

ilr_value_type_t * ilr_type_double(void) {
  return ilr_type_init(ilr_double, 1);
}

ilr_value_type_t * ilr_type_int(unsigned short size) {
  assert(size > 0);
  // Allcoate a value with an extra slot for bit count
  ilr_value_type_t * t = ilr_type_init(ilr_int, 2);
  // Store bit count
  t->type[1] = size;
  return t;
}

ilr_value_type_t * ilr_type_pointer(ilr_value_type_t * element_type) {
  // Allocate enough space to store entire pointee type
  ilr_value_type_t * t = ilr_type_init(ilr_pointer, element_type->size + 1);
  // Copy pointee
  memcpy(&(t->type[1]), element_type->type, sizeof(ilr_element_t) * element_type->size);
  return t;
}

// FIXME number of bits in size parameter
ilr_value_type_t * ilr_type_array(unsigned short size, ilr_value_type_t * element_type) {
  // Allocate enough space to store entire pointee type
  ilr_value_type_t * t = ilr_type_init(ilr_array, element_type->size + 2);
  // Set size
  t->type[1] = size;
  // Copy element type
  memcpy(&(t->type[2]), element_type->type, sizeof(ilr_element_t) * element_type->size);
  return t;
}

ilr_value_type_t * ilr_type_vector(unsigned short size, ilr_value_type_t * element_type) {
  // Allocate enough space to store entire pointee type
  ilr_value_type_t * t = ilr_type_init(ilr_vector, element_type->size + 2);
  // Set size
  t->type[1] = size;
  // Copy element type
  memcpy(&(t->type[2]), element_type->type, sizeof(ilr_element_t) * element_type->size);
  return t;
}

ilr_value_type_t * ilr_type_struct(unsigned num_fields, ilr_value_type_t ** element_types) {
  unsigned i, offset;

  assert(num_fields != 0);

  // Calculate size needed for the fields
  offset = 0;
  for (i = 0; i < num_fields; ++i) {
    offset += element_types[i]->size;
  }

  // Init and set number of fields
  ilr_value_type_t * t = ilr_type_init(ilr_struct, offset + 2);
  t->type[1] = num_fields;

  // Copy type data over
  offset = 2;
  for (i = 0; i < num_fields; ++i) {
    memcpy(&(t->type[offset]), element_types[i]->type,
      sizeof(ilr_element_t) * element_types[i]->size);
    offset += element_types[i]->size;
  }

  return t;
}

ilr_value_type_t * ilr_type_func(
  ilr_value_type_t * return_type, unsigned num_args,
  ilr_value_type_t ** argument_types) {
  unsigned i, total_size;

  // Calculate the size needed
  total_size = return_type->size + 2;
  for (i = 0; i < num_args; ++i) {
    total_size += argument_types[i]->size;
  }

  // Init
  ilr_value_type_t * t = ilr_type_init(ilr_func, total_size);
  // Number of arguments goes in first
  t->type[1] = num_args;
  // Then the return type
  memcpy(&(t->type[2]), return_type->type, sizeof(ilr_element_t) * return_type->size);

  // Copy the arguments
  unsigned offset = return_type->size + 2;
  for (i = 0; i < num_args; ++i) {
    memcpy(t->type + offset, argument_types[i]->type,
      sizeof(ilr_element_t) * argument_types[i]->size);
    offset += argument_types[i]->size;
  }

  return t;
}

void ilr_type_free(ilr_value_type_t ** t) {
  free((*t)->type);
  free(*t);
  *t = NULL;
}

unsigned ilr_get_int_width(ilr_value_type_t * t) {
  assert(t->type[0] == ilr_int);
  return t->type[1];
}

unsigned short ilr_get_array_size(ilr_value_type_t * arr_type) {
  assert(arr_type->type[0] == ilr_array);
  return arr_type->type[1];
}

ilr_value_type_t * ilr_get_array_element_type(ilr_value_type_t * t) {
  assert(t->type[0] == ilr_array);
  // FIXME larger than short array sizes...
  ilr_value_type_t * elem = ilr_type_init(t->type[2], t->size - 2);
  memcpy(&(elem->type[1]), &(t->type[3]), sizeof(ilr_element_t) * (elem->size - 1));
  return elem;
}

unsigned short ilr_get_vector_size(ilr_value_type_t * vec_type) {
  assert(vec_type->type[0] == ilr_vector);
  return vec_type->type[1];
}

ilr_value_type_t * ilr_get_vector_lane_type(ilr_value_type_t * t) {
  assert(t->type[0] == ilr_vector);
  ilr_value_type_t * elem = ilr_type_init(t->type[2], t->size - 2);
  memcpy(&(elem->type[1]), &(t->type[3]), sizeof(ilr_element_t) * (elem->size - 1));
  return elem;
}

ilr_value_type_t * ilr_get_pointee_type(ilr_value_type_t * t) {
  assert(t->type[0] == ilr_pointer);
  ilr_value_type_t * pointee = ilr_type_init(t->type[1], t->size - 1);
  memcpy(&(pointee->type[1]), &(t->type[2]), sizeof(ilr_element_t) * (pointee->size - 1));
  return pointee;
}

unsigned short ilr_get_struct_size(ilr_value_type_t * t) {
  assert(t->type[0] == ilr_struct);
  return(t->type[1]);
}

// Init from an entry in a list of types
ilr_value_type_t * ilr_type_init_from_list(ilr_element_t * types,
  unsigned size, unsigned index) {
  unsigned i;
  for (i = 0; i < index; ++i) {
    unsigned entry_size = ilr_type_get_unboxed_size(types, size);
    types += entry_size;
    size -= entry_size;
  }

  size = ilr_type_get_unboxed_size(types, size);
  ilr_value_type_t * t = ilr_type_init(types[0], size);
  memcpy(t->type + 1, types + 1, sizeof(ilr_element_t) * (size - 1));

  return t;
}

ilr_value_type_t * ilr_get_struct_field_type(ilr_value_type_t * t, unsigned index) {
  assert(t->type[0] == ilr_struct);
  assert(index < t->type[1]);
  return ilr_type_init_from_list(t->type + 2, t->size, index);
}

ilr_value_type_t * ilr_get_func_return_type(ilr_value_type_t * t) {
  assert(t->type[0] == ilr_func);
  ilr_value_type_t * ret
    = ilr_type_init(t->type[2], ilr_type_get_unboxed_size(t->type + 2, t->size - 2));
  memcpy(ret->type + 1, t->type + 3, sizeof(ilr_element_t) * (ret->size - 1));
  return ret;
}

unsigned short ilr_get_func_num_args(ilr_value_type_t * t) {
  assert(t->type[0] == ilr_func);
  return t->type[1];
}


ilr_value_type_t * ilr_get_func_argument_type(ilr_value_type_t * t, unsigned index) {
  assert(t->type[0] == ilr_func);
  assert(index < t->type[1]);
  return ilr_type_init_from_list(t->type + 2, t->size, index + 1);
}

