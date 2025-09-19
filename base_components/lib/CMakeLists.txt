add_library(basecomponentsLib STATIC half_adder.cpp full_adder.cpp delay.cpp toggledbit.cpp word_maker.cpp word_splitter.cpp word_switch_in.cpp toggledword.cpp word_output.cpp bitmemory.cpp word_wire.cpp word_adder.cpp word_and.cpp word_mux.cpp word_nand.cpp word_nor.cpp word_not.cpp word_or.cpp word_xor.cpp word_neg.cpp word_memory.cpp counter.cpp program.cpp byte_decoder.cpp)

target_link_libraries(basecomponentsLib PRIVATE baselogicLib derivedlogicLib)

target_include_directories(basecomponentsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS basecomponentsLib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)

install(FILES half_adder.hpp full_adder.hpp delay.hpp toggledbit.hpp wordmicrocircuit.hpp word_maker.hpp word_splitter.hpp word_switch_in.hpp toggled_word.hpp word_output.hpp bitmemory.hpp word_wire.hpp word_adder.hpp word_and.hpp word_mux.hpp word_nand.hpp word_nor.hpp word_not.hpp word_or.hpp word_xor.hpp word_neg.hpp word_memory.hpp counter.hpp program.hpp byte_decoder.hpp DESTINATION include)
