add_library(derivedcomponentsLib STATIC source_dest_decoder.cpp register_plus.cpp conditional_unit.cpp arithmetic_logic_unit.cpp RAM.cpp)

target_link_libraries(derivedcomponentsLib PRIVATE baselogicLib derivedlogicLib basecomponentsLib)

target_include_directories(derivedcomponentsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS derivedcomponentsLib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)

install(FILES source_dest_decoder.hpp register_plus.hpp conditional_unit.hpp arithmetic_logic_unit.hpp RAM.hpp DESTINATION include)
