  # add library using the specified source files                                  
add_library(baselogicLib STATIC switch_in.cpp output.cpp nand.cpp wire.cpp) 
        
  # add include directories to our target library                                 
  # (PUBLIC because users of the library will need the                            
  # include file square.hpp)                                                      
target_include_directories(baselogicLib PUBLIC ./)                                                                                  
  # specify install rules (for our square library squareLib)                      
install(TARGETS baselogicLib                                                       
        ARCHIVE DESTINATION lib                                                 
        LIBRARY DESTINATION lib                                                 
        RUNTIME DESTINATION bin                                                 
       )                                                                        
                                                                                  
  # specify install rules for the header                                          
install(FILES gate.hpp switch_in.hpp output.hpp nand.hpp wire.hpp DESTINATION include)  
