/* \file types.c Test type manipulations */

#include <stdbool.h>
#include <stdlib.h>

#include "check.h"

#include "type_private.h"

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

  ilr_value_type_t * p_entry = ilr_type_int(32);
  p = ilr_type_pointer(p_entry);
  CHECK(p->size == p_entry->size + 1);
  CHECK(p->type[0] == ilr_pointer);
  for (i = 0; i < p_entry->size; ++i) {
    CHECK(p->type[i + 1] == p_entry->type[i]);
  }
  ilr_type_free(&p);
  ilr_type_free(&p_entry);
  CHECK(p == NULL);
  CHECK(p_entry == NULL);

  p_entry = ilr_type_float();
  p = ilr_type_array(10, p_entry);
  CHECK(p->size == p_entry->size + 2);
  CHECK(p->type[0] == ilr_array);
  CHECK(p->type[1] == 10);
  for (i = 0; i < p_entry->size; ++i) {
    CHECK(p->type[i + 2] == p_entry->type[i]);
  }
  ilr_type_free(&p);
  ilr_type_free(&p_entry);
  CHECK(p == NULL);
  CHECK(p_entry == NULL);

  p_entry = ilr_type_double();
  p = ilr_type_scaled(4, p_entry);
  CHECK(p->size == p_entry->size + 2);
  CHECK(p->type[0] == ilr_scaled);
  CHECK(p->type[1] == 4);
  for (i = 0; i < p_entry->size; ++i) {
    CHECK(p->type[i + 2] == p_entry->type[i]);
  }
  ilr_type_free(&p);
  ilr_type_free(&p_entry);
  CHECK(p == NULL);
  CHECK(p_entry == NULL);

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

  types = realloc(types, sizeof(ilr_value_type_t *) * 3);
  types[0] = ilr_type_double();
  types[1] = ilr_type_int(32);
  p_entry = ilr_type_int(8);
  types[2] = ilr_type_pointer(p_entry);
  ilr_type_free(&p_entry);
  p_entry = ilr_type_void();  // Now as a return type
  p = ilr_type_func(p_entry, 3, types);
  CHECK(p->type[0] == ilr_func);
  CHECK(p->type[1] == 3);
  CHECK(p->type[2] == ilr_void);
  CHECK(p->type[3] == ilr_double);
  CHECK(p->type[4] == ilr_int);
  CHECK(p->type[5] == 32);
  CHECK(p->type[6] == ilr_pointer);
  CHECK(p->type[7] == ilr_int);
  CHECK(p->type[8] == 8);
  ilr_type_free(&p);
  ilr_type_free(&p_entry);
  CHECK(p == NULL);
  CHECK(p_entry == NULL);

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
  p_entry = ilr_get_pointee_type(&t);
  CHECK(p_entry->size == 2);
  CHECK(p_entry->type[0] == ilr_int);
  CHECK(p_entry->type[1] == 16);
  ilr_type_free(&p_entry);
  CHECK(p_entry == NULL);

  t.type[0] = ilr_array;
  t.type[1] = 1000;
  t.type[2] = ilr_double;
  CHECK(ilr_type_get_unboxed_size(t.type, t.size) == t.size);
  CHECK(ilr_type_is(&t) == ilr_array);
  CHECK(ilr_get_array_size(&t) == 1000);
  p_entry = ilr_get_array_element_type(&t);
  CHECK(ilr_type_is(p_entry) == ilr_double);
  ilr_type_free(&p_entry);
  CHECK(p_entry == NULL);

  t.type[0] = ilr_scaled;
  t.type[1] = 4;
  t.type[2] = ilr_float;
  CHECK(ilr_type_get_unboxed_size(t.type, t.size) == t.size);
  CHECK(ilr_type_is(&t) == ilr_scaled);
  CHECK(ilr_get_scaled_size(&t) == 4);
  p_entry = ilr_get_scaled_lane_type(&t);
  CHECK(ilr_type_is(p_entry) == ilr_float);
  ilr_type_free(&p_entry);
  CHECK(p_entry == NULL);

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
  CHECK(ilr_get_struct_size(&t) == 2);
  CHECK(ilr_type_get_unboxed_size(t.type, t.size) == t.size);
  p_entry = ilr_get_struct_field_type(&t, 0);
  CHECK(p_entry->size == 3);
  CHECK(p_entry->type[0] == ilr_pointer);
  CHECK(p_entry->type[1] == ilr_int);
  CHECK(p_entry->type[2] == 8);
  ilr_type_free(&p_entry);
  p_entry = ilr_get_struct_field_type(&t, 1);
  CHECK(p_entry->size == 2);
  CHECK(p_entry->type[0] == ilr_int);
  CHECK(p_entry->type[1] == 64);
  ilr_type_free(&p_entry);

  t.size = 13;
  t.type = realloc(t.type, t.size * sizeof(ilr_element_t));
  t.type[0] = ilr_func;
  t.type[1] = 3;
  t.type[2] = ilr_int;
  t.type[3] = 9;
  t.type[4] = ilr_int;
  t.type[5] = 1;
  t.type[6] = ilr_pointer;
  t.type[7] = ilr_float;
  t.type[8] = ilr_pointer;
  t.type[9] = ilr_struct;
  t.type[10] = 2;
  t.type[11] = ilr_float;
  t.type[12] = ilr_float;
  CHECK(ilr_type_is(&t) == ilr_func);
  CHECK(ilr_type_get_unboxed_size(t.type, t.size) == t.size);
  CHECK(ilr_get_func_num_args(&t) == 3);
  p_entry = ilr_get_func_return_type(&t);
  CHECK(p_entry->size == 2);
  CHECK(p_entry->type[0] == ilr_int);
  CHECK(p_entry->type[1] == 9);
  ilr_type_free(&p_entry);
  p_entry = ilr_get_func_argument_type(&t, 0);
  CHECK(p_entry->size == 2);
  CHECK(p_entry->type[0] == ilr_int);
  CHECK(p_entry->type[1] == 1);
  ilr_type_free(&p_entry);
  p_entry = ilr_get_func_argument_type(&t, 1);
  CHECK(p_entry->size == 2);
  CHECK(p_entry->type[0] == ilr_pointer);
  CHECK(p_entry->type[1] == ilr_float);
  ilr_type_free(&p_entry);
  p_entry = ilr_get_func_argument_type(&t, 2);
  CHECK(p_entry->size == 5);
  CHECK(p_entry->type[0] == ilr_pointer);
  CHECK(p_entry->type[1] == ilr_struct);
  CHECK(p_entry->type[2] == 2);
  CHECK(p_entry->type[3] == ilr_float);
  CHECK(p_entry->type[4] == ilr_float);
  ilr_type_free(&p_entry);

  free(t.type);

  return check_report();
}
