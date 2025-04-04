#add_library(basecomponentsLib STATIC half_adder.cpp full_adder.cpp delay.cpp toggledbit.cpp word_maker.cpp word_splitter.cpp word_switch_in.cpp byte_adder.cpp byte_not.cpp byte_or.cpp byte_neg.cpp toggledword.cpp byte_nor.cpp byte_nand.cpp byte_and.cpp byte_mux.cpp word_output.cpp bitmemory.cpp bytememory.cpp counter.cpp program.cpp word_wire.cpp)

add_library(basecomponentsLib STATIC half_adder.cpp full_adder.cpp delay.cpp toggledbit.cpp word_maker.cpp word_splitter.cpp word_switch_in.cpp toggledword.cpp word_output.cpp bitmemory.cpp word_wire.cpp word_adder.cpp)

target_link_libraries(basecomponentsLib PRIVATE baselogicLib derivedlogicLib)

target_include_directories(basecomponentsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS basecomponentsLib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)

#install(FILES half_adder.hpp full_adder.hpp delay.hpp toggledbit.hpp wordmicrocircuit.hpp word_maker.hpp word_splitter.hpp word_switch_in.hpp byte_adder.hpp byte_not.hpp byte_or.hpp byte_neg.hpp toggledword.cpp byte_nor.hpp byte_nand.hpp byte_and.hpp byte_mux.hpp word_output.hpp bitmemory.hpp bytememory.hpp counter.hpp program.hpp word_wire.hpp DESTINATION include)

install(FILES half_adder.hpp full_adder.hpp delay.hpp toggledbit.hpp wordmicrocircuit.hpp word_maker.hpp word_splitter.hpp word_switch_in.hpp toggled_word.hpp word_output.hpp bitmemory.hpp word_wire.hpp word_adder.hpp DESTINATION include)
