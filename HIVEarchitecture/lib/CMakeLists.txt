add_library(HIVELib STATIC ConditionalUnit.cpp)

target_link_libraries(HIVELib PRIVATE derivedcomponentsLib basecomponentsLib baselogicLib derivedlogicLib)

target_include_directories(HIVELib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS HIVELib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)

install(FILES ConditionalUnit.hpp DESTINATION include)
