# require minimum version of CMake                                              
cmake_minimum_required(VERSION 3.15)                                            
                                                                                  
  # set name of project                                                           
project(baseLogic)                                                                 
                                                                                  
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

  # setting warning compiler flags                                                
add_compile_options(-Wall -Wextra -Wpedantic)                                   
                                                                                  
  # add a subdirectory to the build (here lib contains the                        
  # CMakeLists.txt with the square library)                                       
add_subdirectory(lib)                                                           
                                                                                  
  # add executable to the project using the specified source files                
add_executable(base_test0 base_logic_tests/TC_Crude_Awakening.cpp)                                                 
add_executable(base_test1 base_logic_tests/TC_NAND_Gate.cpp)
                                                                                  
  # specify that we need the square library (squareLib)                           
target_link_libraries(base_test0 baselogicLib)                                 
target_link_libraries(base_test1 baselogicLib)
                                                                                  
  # specify install rules                                                         
install(TARGETS base_test0 base_test1 DESTINATION bin)
