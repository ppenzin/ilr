enable_testing()

# TODO valgrind option

include_directories(${ILR_CORE_SRC_DIR})

macro(add_ilr_test name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} ilr)

  add_ilr_test_command(${name} ${ARGN})
endmacro(add_ilr_test)

add_ilr_test(empty_module empty_module.c)
add_ilr_test(types types.c)
