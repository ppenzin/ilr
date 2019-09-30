enable_testing()

# Test helpers
include_directories(include)
add_subdirectory(util)

macro(add_ilr_cxx_test name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} ilrMock ilrcxx testVerify)

  add_ilr_test_command(${name} ${ARGN})
endmacro(add_ilr_cxx_test)

add_ilr_cxx_test(module-cpp module.cpp)
add_ilr_cxx_test(type-cpp type.cpp)
