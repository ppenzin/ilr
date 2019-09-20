#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "type_private.h"

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

