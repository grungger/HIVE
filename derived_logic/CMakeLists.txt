cmake_minimum_required(VERSION 3.15)

project(derivedLogic)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wpedantic -Wextra)

add_subdirectory(lib)

add_executable(derived_twog_test derived_logic_tests/two_gate_tests.cpp)
add_executable(derived_threeg_test derived_logic_tests/three_input_gates.cpp)
add_executable(decoding derived_logic_tests/decoding.cpp)

target_link_libraries(derived_twog_test PRIVATE derivedlogicLib baselogicLib)
target_link_libraries(derived_threeg_test PRIVATE derivedlogicLib baselogicLib)
target_link_libraries(decoding PRIVATE derivedlogicLib baselogicLib)

install(TARGETS derived_twog_test derived_threeg_test decoding DESTINATION bin)
