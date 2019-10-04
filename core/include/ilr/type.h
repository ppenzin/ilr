/// \file type.h
/// Describes value types in ILR

#ifndef ILR_TYPE_H
#define ILR_TYPE_H

// TODO type restrictions
// - Types of vector lane elements
// - Types of array elements
// - Structures with no fields
// - Use of void
// - Use of function type

/// Value types
enum ilr_type {
  // 'void' type
  ilr_void = 0,
  /// Integer, takes a type parameter indicating width
  ilr_int,
  /// 32-bit floating point number
  ilr_float,
  /// 64-bit floating point number
  ilr_double,
  /// Pointer to a value, takes a type parameter indicating type of the pointee
  ilr_pointer,
  /// Array of values, takes two parameters: length, and element type
  ilr_array,
  /// Vector, takes two parameters: length (# elements) and lane type
  /// intended for performing the same operation on all lanes
  ilr_vector,
  /// C-style structure, parameters: number of fields, followed by types of the fields
  ilr_struct,
  /// Function, parameters: return type, number of aguments, types of arguments
  ilr_func
};

/// Value type
typedef struct ilr_value_type_ ilr_value_type_t;

// Create type

/// Create void type
ilr_value_type_t * ilr_type_void(void);

/// Create float type
ilr_value_type_t * ilr_type_float(void);
/// Create double type
ilr_value_type_t * ilr_type_double(void);

/// Create int type
/// \param size (size in bits)
ilr_value_type_t * ilr_type_int(unsigned short size);

/// Create pointer type
/// \param pointee type
ilr_value_type_t * ilr_type_pointer(ilr_value_type_t * element_type);

/// Create array type
///
/// \param size number of elements
/// \param element_type type of array elements
///
/// FIXME ammount of size to support
ilr_value_type_t * ilr_type_array(unsigned short size, ilr_value_type_t * element_type);

/// Create vector type
///
/// \param size number of lanes
/// \param element_type type of each lane
///
/// Vectors support only 16 bits of size
ilr_value_type_t * ilr_type_vector(unsigned short size, ilr_value_type_t * element_type);

/// Create structure type
///
/// \param size number of fields
/// \param element_types array of types for the fields
ilr_value_type_t * ilr_type_struct(unsigned num_fields, ilr_value_type_t ** element_types);

/// Create function type
///
/// \param return_type function return type
/// \param num_args number of arguments
/// \param argument_types array of types representing the arguments
ilr_value_type_t * ilr_type_func(ilr_value_type_t * return_type, unsigned num_args, ilr_value_type_t ** argument_types);

/// Free type
void ilr_type_free(ilr_value_type_t ** t);

/// Test type
enum ilr_type ilr_type_is(ilr_value_type_t * t);

// Type specific manipulations

/// Get a width for an int
unsigned ilr_get_int_width(ilr_value_type_t * t);

/// Get type of the pointee for a pointer type
ilr_value_type_t * ilr_get_pointee_type(ilr_value_type_t * t);

/// Get array size
unsigned short ilr_get_array_size(ilr_value_type_t * arr_type);

/// Get array element type
ilr_value_type_t * ilr_get_array_element_type(ilr_value_type_t * t);

/// Get vector size
unsigned short ilr_get_vector_size(ilr_value_type_t * vec_type);

/// Get vector lane type
ilr_value_type_t * ilr_get_vector_lane_type(ilr_value_type_t * t);

/// Get number of fields in a structure type
unsigned short ilr_get_struct_size(ilr_value_type_t * t);

/// Get type of structure's field
ilr_value_type_t * ilr_get_struct_field_type(ilr_value_type_t * t, unsigned index);

// TODO get field types as an array

/// Get function return type
ilr_value_type_t * ilr_get_func_return_type(ilr_value_type_t * t);

/// Get number of arguments for a function
unsigned short ilr_get_func_num_args(ilr_value_type_t * t);

/// Get an type of an argument
ilr_value_type_t * ilr_get_func_argument_type(ilr_value_type_t * t, unsigned index);

// TODO get argument types as an array

#endif // ILR_TYPE_H
