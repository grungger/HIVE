add_library(basecomponentsLib STATIC half_adder.cpp full_adder.cpp delay.cpp toggledbit.cpp byte_maker.cpp byte_splitter.cpp byteswitch_in.cpp byte_adder.cpp byte_not.cpp byte_or.cpp byte_neg.cpp toggledbyte.cpp byte_nor.cpp byte_nand.cpp byte_and.cpp byte_mux.cpp byteoutput.cpp bitmemory.cpp bytememory.cpp counter.cpp program.cpp)

target_link_libraries(basecomponentsLib PRIVATE baselogicLib derivedlogicLib)

target_include_directories(basecomponentsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS basecomponentsLib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)

install(FILES half_adder.hpp full_adder.hpp delay.hpp toggledbit.hpp bytemicrocircuit.hpp byte_maker.hpp byte_splitter.hpp byteswitch_in.hpp byte_adder.hpp byte_not.hpp byte_or.hpp byte_neg.hpp toggledbyte.cpp byte_nor.hpp byte_nand.hpp byte_and.hpp byte_mux.hpp byteoutput.hpp bitmemory.hpp bytememory.hpp counter.hpp program.hpp DESTINATION include)
