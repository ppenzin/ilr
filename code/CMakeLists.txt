cmake_minimum_required(VERSION 3.5)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  # Allow standalone builds
  project(ILRCore)
  set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
  include_directories(include)

  include(tests)

endif (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

include(CheckCCompilerFlag)

# TODO other spellings of that option
set(POINTER_TYPE_ERROR_FLAG "-Werror=incompatible-pointer-types")

# Mismatched pointer type should be an error
CHECK_C_COMPILER_FLAG(${POINTER_TYPE_ERROR_FLAG} POINTER_TYPE_ERROR_SUPPORT)
if (${POINTER_TYPE_ERROR_SUPPORT})
  set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${POINTER_TYPE_ERROR_FLAG})
endif (${POINTER_TYPE_ERROR_SUPPORT})

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(ILR_CORE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(test)

