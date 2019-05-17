cmake_minimum_required(VERSION 3.0)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  # Allow standalone builds
  project(ILRCore)
endif (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)

