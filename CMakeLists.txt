cmake_minimum_required(VERSION 3.5)

project(ILR)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include_directories(code/include)

enable_testing()

include(tests)

add_subdirectory(code)
