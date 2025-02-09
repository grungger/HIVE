add_library(derivedcomponentsLib STATIC arithmetic_engine.cpp)

target_link_libraries(derivedcomponentsLib PRIVATE basecomponentsLib derivedlogicLib baselogicLib)

target_include_directories(derivedcomponentsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS derivedcomponentsLib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)

install(FILES arithmetic_engine.hpp
	DESTINATION include)
