#include "variable_int.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

const unsigned lshift = CHAR_BIT * sizeof(ilr_element_t);
// TODO This defined in limits.h, just need to match ilr_element_t
const ilr_element_t max = ~((ilr_element_t)0); // OxFF..F

// FIXME should this be inlined in the header?

unsigned ilr_varint_from_size_t(ilr_element_t * arr_out, size_t value) {
  const unsigned size = (sizeof(size_t) / sizeof(ilr_element_t)) + 1;
  size_t mask = max;
  unsigned i;

  for (i = 0; i < size; ++i) {
    if (value < max) {
      arr_out[i] = value;
      break;
    }

    value = value - mask;
    mask = mask << lshift;
    arr_out[i] = max;
  }

  return i + 1;
}

size_t ilr_varint_to_size_t(ilr_element_t * arr, size_t size) {
  size_t val, i;

  val = 0;
  for (i = 0; i < size; ++i) {
    if (*arr < max)
      break;

    val = val << lshift;
    val = val | max;

    ++arr;
  }

  // Make sure we did not reach the end of allocated value without finding the tail
  assert(*arr != max);

  val = val + *arr;

  return val;
}


