# Default test target
set(ILR_MAIN_TEST_TARGET check)
# Memory check test target
set(ILR_MEMORY_TEST_TARGET memcheck)
# Name prfix for memcheck tests
set(MEMCHECK_PREFIX "memcheck:")

# Turn memcheck On or Off
set(ILR_TEST_USE_VALGRIND OFF CACHE BOOL "Use valgrind for memory checking")
# Suppress output on failed tests
set(ILR_TEST_SUPPRESS_OUTPUT OFF CACHE BOOL "Don't display output of failed tests")

if (NOT ILR_TEST_SUPPRESS_OUTPUT)
  set(CTEST_ARGS --output-on-failure)
endif (NOT ILR_TEST_SUPPRESS_OUTPUT)

if (ILR_TEST_USE_VALGRIND)
  find_program(VALGRIND_EXE valgrind DOC "Valgrind executable")
  if (NOT VALGRIND_EXE)
    message(FATAL_ERROR "Valgrind executable not found on PATH")
  endif (NOT VALGRIND_EXE)

  add_custom_target(${ILR_MEMORY_TEST_TARGET}
    COMMAND ${CMAKE_CTEST_COMMAND} -R ${MEMCHECK_PREFIX} ${CTEST_ARGS}
    WORKING_DIRECTORY ${CMAKE_BUILD_DIRECTORY}
  )
endif (ILR_TEST_USE_VALGRIND)

add_custom_target(${ILR_MAIN_TEST_TARGET}
  COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_ARGS}
  WORKING_DIRECTORY ${CMAKE_BUILD_DIRECTORY}
)

macro(add_ilr_test_command name)
  add_test(NAME ${name} COMMAND ${name} ${ARGN})

  if (ILR_TEST_USE_VALGRIND)
    add_test(NAME ${MEMCHECK_PREFIX}${name}
      COMMAND ${VALGRIND_EXE}
        --tool=memcheck ${CMAKE_CURRENT_BINARY_DIR}/${name} ${ARGN})
  endif (ILR_TEST_USE_VALGRIND)

  add_dependencies(${ILR_MAIN_TEST_TARGET} ${name})
endmacro(add_ilr_test_command)

