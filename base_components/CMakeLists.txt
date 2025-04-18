cmake_minimum_required(VERSION 3.15)

project(baseComponents)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wpedantic -Wextra)

add_subdirectory(lib)

add_executable(toggledbit_test tests/toggledbit_test.cpp)
add_executable(bitmemory_test tests/bitmemory_test.cpp)
add_executable(hf_adder_test tests/hf_adder_test.cpp)
add_executable(split_combine_test tests/split_combine_test.cpp)
add_executable(word_wire_test tests/word_wire_test.cpp)
add_executable(toggledword_test tests/toggledword_test.cpp)
add_executable(bitwise_op_test tests/bitwise_op_test.cpp)
add_executable(tog_w tests/tog_w.cpp)
add_executable(wordmemory_test tests/wordmemory_test.cpp)
add_executable(mux_test tests/mux_test.cpp)

add_executable(counter_test base_components_tests/counter_test.cpp)

target_link_libraries(toggledbit_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(bitmemory_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(hf_adder_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(split_combine_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(word_wire_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(toggledword_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(bitwise_op_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(tog_w PRIVATE basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(wordmemory_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)
target_link_libraries(mux_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)

target_link_libraries(counter_test PRIVATE basecomponentsLib derivedlogicLib baselogicLib)

install(TARGETS counter_test DESTINATION bin)

add_test(NAME toggledbit_testexe COMMAND toggledbit_test)
add_test(NAME bitmemory_testexe COMMAND bitmemory_test)
add_test(NAME hf_adder_testexe COMMAND hf_adder_test)
add_test(NAME split_combine_testexe COMMAND split_combine_test)
add_test(NAME word_wire_testexe COMMAND word_wire_test)
add_test(NAME toggledword_testexe COMMAND toggledword_test)
add_test(NAME bitwise_op_testexe COMMAND bitwise_op_test)
add_test(NAME tog_wexe COMMAND tog_w)
add_test(NAME wordmemory_testexe COMMAND wordmemory_test)
add_test(NAME mux_testexe COMMAND mux_test)

