#ifndef VARIABLE_INT_H
#define VARIABLE_INT_H

#include "ilr_private.h"
#include <stddef.h>

/// Convert an integer to a an array of ILR elements
///
/// \param arr_out pointer to caller-managed array to write elements to
/// \param value value to convert
/// \return number of elements used
unsigned ilr_varint_from_size_t(ilr_element_t * arr_out, size_t value);
// FIXME ^ number of available elements

/// Get an integer value from array of ILR elements represeting it
///
/// \param arr caller-managed array representing the value
/// \param size maximum number of consumable elements
/// \return integer value from array elements
size_t ilr_varint_to_size_t(ilr_element_t * arr, size_t size);

#endif // VARIABLE_INT_H
