add_library(HIVELib STATIC ConditionalUnit.cpp ArithmeticLogicUnit.cpp)

target_link_libraries(HIVELib PRIVATE derivedcomponentsLib basecomponentsLib baselogicLib derivedlogicLib)

target_include_directories(HIVELib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS HIVELib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)

install(FILES ConditionalUnit.hpp ArithmeticLogicUnit.hpp DESTINATION include)
