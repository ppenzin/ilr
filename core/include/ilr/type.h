/// \file type.h
/// Describes value types in ILR

#ifndef ILR_TYPE_H
#define ILR_TYPE_H

/// Available high level types
enum ilr_type {
  ilr_void = 0,
  ilr_int,
  ilr_float,
  ilr_double,
  ilr_array,
  ilr_pointer,
  ilr_struct,
  ilr_func
};

/// Value type
typedef struct ilr_value_type_ ilr_value_type_t;

/// Create type
///
/// Expected parameters
/// - only kind for double, float, and void
/// - kind, size for int
/// - FIXME rest
ilr_value_type_t * ilr_type_new(enum ilr_type kind, ...);
/// Free type
void ilr_type_free(ilr_value_type_t ** t);

/// Test type
enum ilr_type ilr_type_is(ilr_value_type_t * t);

// Type specific manipulations

/// Get a width for an int
unsigned ilr_get_int_width(ilr_value_type_t * t);

#endif // ILR_TYPE_H
