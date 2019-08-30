enable_testing()

# Test helpers
include_directories(include)
add_subdirectory(util)

macro(add_ilr_test name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} testVerify)

  add_test(NAME ${name} COMMAND ${name} ${ARGN})

  # Create target `check`, force test rebuild
  if (NOT TARGET check)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${name})
  else()
    add_dependencies(check ${name})
  endif()
endmacro(add_ilr_test)

add_ilr_test(module-cpp module.cpp)
add_ilr_test(instructions-cpp instructions.cpp)
