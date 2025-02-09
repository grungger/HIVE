cmake_minimum_required(VERSION 3.15)

project(derivedComponents)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wpedantic -Wextra)

add_subdirectory(lib)

# add_executable(arithmetic_engine_test derived_components_tests/arithmetic_engine_test.cpp)

# target_link_libraries(arithemtic_engine_test PRIVATE derivedcomponentsLib basecomponentsLib derivedlogicLib baselogicLib)

# install(TARGETS arithemtic_engine_test DESTINATION bin)
