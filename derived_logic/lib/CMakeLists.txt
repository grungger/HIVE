add_library(derivedlogicLib STATIC not.cpp and.cpp  nor.cpp or.cpp xor.cpp xnor.cpp and3.cpp or3.cpp onebitdecoder.cpp threebitdecoder.cpp fourbitdecoder.cpp fivebitdecoder.cpp)

target_link_libraries(derivedlogicLib PRIVATE baselogicLib)

target_include_directories(derivedlogicLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS derivedlogicLib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)

install(FILES microcircuit.hpp not.hpp and.hpp nor.hpp or.hpp xor.hpp xnor.hpp and3.hpp or3.hpp onebitdecoder.hpp threebitdecoder.hpp fourbitdecoder.hpp fivebitdecoder.hpp DESTINATION include)
