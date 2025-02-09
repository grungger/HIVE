cmake_minimum_required(VERSION 3.15)

project(circuits)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wpedantic -Wextra)

add_subdirectory(lib)

add_executable(TC_Odd_Ticks circuits_tests/TC_Odd_Ticks.cpp)
add_executable(saving_bits_test circuits_tests/saving_bits.cpp)

target_link_libraries(TC_Odd_Ticks PRIVATE circuitsLib basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(saving_bits_test PRIVATE circuitsLib basecomponentsLib derivedlogicLib baselogicLib)

install(TARGETS TC_Odd_Ticks saving_bits_test DESTINATION bin)
