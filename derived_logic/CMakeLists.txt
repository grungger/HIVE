cmake_minimum_required(VERSION 3.15)

project(derivedLogic)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wpedantic -Wextra)

add_subdirectory(lib)

add_executable(2gate_test tests/2gate_test.cpp)
add_executable(3gate_test tests/3gate_test.cpp)
add_executable(decoding_test tests/decoding_test.cpp)

target_link_libraries(2gate_test PRIVATE derivedlogicLib baselogicLib)
target_link_libraries(3gate_test PRIVATE derivedlogicLib baselogicLib)
target_link_libraries(decoding_test PRIVATE derivedlogicLib baselogicLib)

add_test(NAME 2gate_testexe COMMAND 2gate_test)
add_test(NAME 3gate_testexe COMMAND 3gate_test)
add_test(NAME decoding_testexe COMMAND decoding_test)
