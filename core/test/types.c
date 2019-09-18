/* Test type manipulations */
#include <stdbool.h>

#include "ilr/type.h"

int main(void) {
  bool passed = true;

  ilr_value_type_t * a_void = ilr_type_new(ilr_void);
  ilr_value_type_t * a_float = ilr_type_new(ilr_float);
  ilr_value_type_t * a_double = ilr_type_new(ilr_double);
  ilr_value_type_t * a_bit = ilr_type_new(ilr_int, 1);
  ilr_value_type_t * a_byte = ilr_type_new(ilr_int, 8);
  ilr_value_type_t * an_i40 = ilr_type_new(ilr_int, 40);

  passed = passed
    && (ilr_type_is(a_void) == ilr_void)
    && (ilr_type_is(a_float) == ilr_float)
    && (ilr_type_is(a_double) == ilr_double)
    && (ilr_type_is(a_bit) == ilr_int) && (ilr_get_int_width(a_bit) == 1)
    && (ilr_type_is(a_byte) == ilr_int) && (ilr_get_int_width(a_byte) == 8)
    && (ilr_type_is(an_i40) == ilr_int) && (ilr_get_int_width(an_i40) == 40);

  ilr_type_free(&a_void);
  ilr_type_free(&a_float);
  ilr_type_free(&a_double);
  ilr_type_free(&a_bit);
  ilr_type_free(&a_byte);
  ilr_type_free(&an_i40);

  return (!passed);
}
