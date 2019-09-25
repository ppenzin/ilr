/* Test type manipulations */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "type_private.h"

bool all_passed = true;

void check(const char * label, bool expression) {
  if (!expression) {
    printf("Failed: %s\n", label);
    all_passed = false;
  }
}

#define CHECK(X) check(#X, (X))

int main(void) {
  unsigned i;
  ilr_value_type_t * p;
  ilr_value_type_t t;

  /***** Type initialization *****/

  p = ilr_type_void();
  CHECK(p->size == 1);
  CHECK(p->type[0] == ilr_void);
  ilr_type_free(&p);
  CHECK(p == NULL);

  p = ilr_type_float();
  CHECK(p->size == 1);
  CHECK(p->type[0] == ilr_float);
  ilr_type_free(&p);
  CHECK(p == NULL);

  p = ilr_type_double();
  CHECK(p->size == 1);
  CHECK(p->type[0] == ilr_double);
  ilr_type_free(&p);
  CHECK(p == NULL);

  p = ilr_type_int(3);
  CHECK(p->size == 2);
  CHECK(p->type[0] == ilr_int);
  CHECK(p->type[1] == 3);
  ilr_type_free(&p);
  CHECK(p == NULL);

  ilr_value_type_t * p_elem = ilr_type_int(32);
  p = ilr_type_pointer(p_elem);
  CHECK(p->size == p_elem->size + 1);
  CHECK(p->type[0] == ilr_pointer);
  for (i = 0; i < p_elem->size; ++i) {
    CHECK(p->type[i + 1] == p_elem->type[i]);
  }
  ilr_type_free(&p);
  ilr_type_free(&p_elem);
  CHECK(p == NULL);
  CHECK(p_elem == NULL);

  p_elem = ilr_type_float();
  p = ilr_type_array(10, p_elem);
  CHECK(p->size == p_elem->size + 2);
  CHECK(p->type[0] == ilr_array);
  CHECK(p->type[1] == 10);
  for (i = 0; i < p_elem->size; ++i) {
    CHECK(p->type[i + 2] == p_elem->type[i]);
  }
  ilr_type_free(&p);
  ilr_type_free(&p_elem);
  CHECK(p == NULL);
  CHECK(p_elem == NULL);

  p_elem = ilr_type_double();
  p = ilr_type_vector(4, p_elem);
  CHECK(p->size == p_elem->size + 2);
  CHECK(p->type[0] == ilr_vector);
  CHECK(p->type[1] == 4);
  for (i = 0; i < p_elem->size; ++i) {
    CHECK(p->type[i + 2] == p_elem->type[i]);
  }
  ilr_type_free(&p);
  ilr_type_free(&p_elem);
  CHECK(p == NULL);
  CHECK(p_elem == NULL);

  ilr_value_type_t ** types = malloc(sizeof(ilr_value_type_t *) * 2);
  types[0] = ilr_type_float();
  types[1] = ilr_type_int(64);
  p = ilr_type_struct(2, types);
  CHECK(p->size == 5);
  CHECK(p->type[0] == ilr_struct);
  CHECK(p->type[1] == 2);
  CHECK(p->type[2] == ilr_float);
  CHECK(p->type[3] == ilr_int);
  CHECK(p->type[4] == 64);
  ilr_type_free(&types[0]);
  ilr_type_free(&types[1]);

  free(types);


  /***** Type checks *****/

  t.size = 1;
  t.type = malloc(sizeof(ilr_element_t));
  t.type[0] = ilr_void;
  CHECK(ilr_type_is(&t) == ilr_void);
  t.type[0] = ilr_float;
  CHECK(ilr_type_is(&t) == ilr_float);
  t.type[0] = ilr_double;
  CHECK(ilr_type_is(&t) == ilr_double);

  t.size = 2;
  t.type = realloc(t.type, t.size * sizeof(ilr_element_t));
  t.type[0] = ilr_int;
  t.type[1] = 8;
  CHECK(ilr_type_get_unboxed_size(t.type, t.size) == t.size);
  CHECK(ilr_type_is(&t) == ilr_int);
  CHECK(ilr_get_int_width(&t) == 8);

  t.size = 3;
  t.type = realloc(t.type, t.size * sizeof(ilr_element_t));
  t.type[0] = ilr_pointer;
  t.type[1] = ilr_int;
  t.type[2] = 16;
  CHECK(ilr_type_get_unboxed_size(t.type, t.size) == t.size);
  CHECK(ilr_type_is(&t) == ilr_pointer);
  p_elem = ilr_get_pointee_type(&t);
  CHECK(p_elem->size == 2);
  CHECK(p_elem->type[0] == ilr_int);
  CHECK(p_elem->type[1] == 16);
  ilr_type_free(&p_elem);
  CHECK(p_elem == NULL);

  t.type[0] = ilr_array;
  t.type[1] = 1000;
  t.type[2] = ilr_double;
  CHECK(ilr_type_get_unboxed_size(t.type, t.size) == t.size);
  CHECK(ilr_type_is(&t) == ilr_array);
  CHECK(ilr_get_array_size(&t) == 1000);
  p_elem = ilr_get_array_element_type(&t);
  CHECK(ilr_type_is(p_elem) == ilr_double);
  ilr_type_free(&p_elem);
  CHECK(p_elem == NULL);

  t.type[0] = ilr_vector;
  t.type[1] = 4;
  t.type[2] = ilr_float;
  CHECK(ilr_type_get_unboxed_size(t.type, t.size) == t.size);
  CHECK(ilr_type_is(&t) == ilr_vector);
  CHECK(ilr_get_vector_size(&t) == 4);
  p_elem = ilr_get_vector_lane_type(&t);
  CHECK(ilr_type_is(p_elem) == ilr_float);
  ilr_type_free(&p_elem);
  CHECK(p_elem == NULL);

  t.size = 7;
  t.type = realloc(t.type, t.size * sizeof(ilr_element_t));
  t.type[0] = ilr_struct;
  t.type[1] = 2;
  t.type[2] = ilr_pointer;
  t.type[3] = ilr_int;
  t.type[4] = 8;
  t.type[5] = ilr_int;
  t.type[6] = 64;
  CHECK(ilr_type_is(&t) == ilr_struct);
  CHECK(ilr_type_get_unboxed_size(t.type, t.size) == t.size);
  p_elem = ilr_get_struct_field_type(&t, 0);
  CHECK(p_elem->size == 3);
  CHECK(p_elem->type[0] == ilr_pointer);
  CHECK(p_elem->type[1] == ilr_int);
  CHECK(p_elem->type[2] == 8);
  ilr_type_free(&p_elem);
  p_elem = ilr_get_struct_field_type(&t, 1);
  CHECK(p_elem->size == 2);
  CHECK(p_elem->type[0] == ilr_int);
  CHECK(p_elem->type[1] == 64);
  ilr_type_free(&p_elem);

  free(t.type);

  return (!all_passed);
}
