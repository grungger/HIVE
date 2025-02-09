add_library(circuitsLib STATIC foo.cpp)

target_link_libraries(circuitsLib PRIVATE basecomponentsLib PRIVATE baselogicLib derivedlogicLib)

target_include_directories(circuitsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS circuitsLib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)

install(FILES circuit.hpp DESTINATION include)
