# Test target to be used acorss various components
set(ILR_TEST_TARGET check)

add_custom_target(${ILR_TEST_TARGET}
  COMMAND ${CMAKE_CTEST_COMMAND}
  WORKING_DIRECTORY ${CMAKE_BUILD_DIRECTORY}
)

macro(add_ilr_test_command name)
  add_test(NAME ${name} COMMAND ${name} ${ARGN})

  add_dependencies(${ILR_TEST_TARGET} ${name})
endmacro(add_ilr_test_command)

