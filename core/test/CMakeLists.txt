enable_testing()

add_subdirectory(util)

include_directories(${ILR_CORE_SRC_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/util)

macro(add_ilr_test name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} ilr testcheck)

  add_ilr_test_command(${name} ${ARGN})
endmacro(add_ilr_test)

add_ilr_test(empty_module empty_module.c)
add_ilr_test(instructions instructions.c)
add_ilr_test(types types.c)
