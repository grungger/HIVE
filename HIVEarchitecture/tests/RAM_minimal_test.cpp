/*********************************
 * @file RAM_minimal_test.cpp
 *********************************/
// Includes:
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include "RAM.hpp"
#include "register_plus.hpp"
#include "word_maker.hpp"
#include "word_mux.hpp"
#include <sstream>
#include <iostream>
#include <array>

using namespace Virtual;

int main() {

// std::stringstream buffer;
// std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
Switch_in load(false);
Switch_in save(false);
WordSwitch_in inputVal(0);

Switch_in compCopy(false);
Switch_in Atog(false);
Switch_in Btog(false);
ByteSwitch_in Aad(0);
ByteSwitch_in Bad(0);
WordSwitch_in inputValRAM(0);

RegisterMax reg(
		load.release_output(0),
		save.release_output(0),
		inputVal.release_word_output(0));

WordMUX mux(
		load.release_output(0),
		inputValRAM.release_word_output(0),
		reg.release_word_output(0));

WordByter wb(
		reg.release_word_output(0));

ByteMUX muxad(
		load.release_output(0),
		Aad.release_byte_output(0),
		wb.release_byte_output(0));

RAM ram(
		compCopy.release_output(0),
		Atog.release_output(0),
		Btog.release_output(0),
		muxad.release_byte_output(0),
		Bad.release_byte_output(0),
		mux.release_word_output(0) );

save.change_state(true);
inputVal.change_state(17);
inputValRAM.change_state(13);
Aad.change_state(3);
Bad.change_state(5);
compCopy.change_state(true);
Btog.change_state(true);
reg.compute_output();
mux.compute_output();
wb.compute_output();
muxad.compute_output();
ram.compute_output();
reg.memory_release();
ram.memory_release();
reg.print_out();
ram.print_out();
ram.printRAM();
}


