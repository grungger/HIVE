/*********************************
 * @file source_dest_decoder_test.cpp
 *
 * @brief The test is called source_dest_decoder_test.
 *********************************/
// Includes:
#include "word_switch_in.hpp"
#include "source_dest_decoder.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteSwitch_in input(0);
SourceDestDecoder dec(input.release_byte_output(0));
dec.compute_output();
dec.print_out();
input.change_state(1);
dec.compute_output();
dec.print_out();
input.change_state(2);
dec.compute_output();
dec.print_out();
input.change_state(6);
dec.compute_output();
dec.print_out();
input.change_state(8);
dec.compute_output();
dec.print_out();
input.change_state(16);
dec.compute_output();
dec.print_out();
input.change_state(32);
dec.compute_output();
dec.print_out();
input.change_state(56);
dec.compute_output();
dec.print_out();
input.change_state(128);
dec.compute_output();
dec.print_out();
input.change_state(192);
dec.compute_output();
dec.print_out();
input.change_state(255);
dec.compute_output();
dec.print_out();
input.change_state(49);
dec.compute_output();
dec.print_out();
input.change_state(204); // 128 + 64 + 8 + 4
dec.compute_output();
dec.print_out();

std::cout.rdbuf(old);
std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("10000000100000001000b") + 
					"01000000100000001000b" +
					"00100000100000001000b" +
					"00000010100000001000b" +
					"10000000010000001000b" +
					"10000000001000001000b" +
					"10000000000010001000b" +
					"10000000000000011000b" +
					"10000000100000000010b" +
					"10000000100000000001b" +
					"00000001000000010001b" +
					"01000000000000101000b" +
					"00001000010000000001b";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}


