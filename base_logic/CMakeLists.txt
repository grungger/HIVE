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
add_executable(io_test tests/logictest0.cpp)
add_executable(nand_test tests/logictest1.cpp)

  # specify that we need the square library (squareLib)                           
target_link_libraries(io_test baselogicLib)                                 
target_link_libraries(nand_test baselogicLib)

  # specify install rules
add_test(NAME io_testexe COMMAND io_test) 
add_test(NAME nand_testexe COMMAND nand_test)
