cmake_minimum_required(VERSION 3.15)

project(HIVE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wpedantic -Wextra)

add_subdirectory(lib)

add_executable(condition_test ./tests/conditional_unit_HIVE_test.cpp)
add_executable(alu_test ./tests/alu_HIVE_test.cpp)

target_link_libraries(condition_test PRIVATE HIVELib derivedcomponentsLib basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(alu_test PRIVATE HIVELib derivedcomponentsLib basecomponentsLib derivedlogicLib baselogicLib)

add_test(NAME condition_test COMMAND condition_test)
add_test(NAME alu_test COMMAND alu_test)
