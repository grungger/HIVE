/*********************************
 * @file conditional_unit_test.cpp
 *********************************/
// Includes:
#include "word_switch_in.hpp"
#include "conditional_unit.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteSwitch_in condition(0);
ByteSwitch_in input(0);
ConditionalUnit dec(condition.release_byte_output(0),
			input.release_byte_output(0));
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

condition.change_state(1);
input.change_state(8);
dec.compute_output();
dec.print_out();
input.change_state(16);
dec.compute_output();
dec.print_out();
input.change_state(0);
dec.compute_output();
dec.print_out();
input.change_state(56);
dec.compute_output();
dec.print_out();

condition.change_state(2);
input.change_state(128);
dec.compute_output();
dec.print_out();
input.change_state(192);
dec.compute_output();
dec.print_out();
input.change_state(0);
dec.compute_output();
dec.print_out();
input.change_state(49);
dec.compute_output();
dec.print_out();

condition.change_state(3);
input.change_state(128);
dec.compute_output();
dec.print_out();
input.change_state(192);
dec.compute_output();
dec.print_out();
input.change_state(0);
dec.compute_output();
dec.print_out();
input.change_state(49);
dec.compute_output();
dec.print_out();

condition.change_state(4);
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

condition.change_state(5);
input.change_state(12);
dec.compute_output();
dec.print_out();
input.change_state(0);
dec.compute_output();
dec.print_out();
input.change_state(255);
dec.compute_output();
dec.print_out();
input.change_state(49);
dec.compute_output();
dec.print_out();

condition.change_state(6);
input.change_state(128);
dec.compute_output();
dec.print_out();
input.change_state(0);
dec.compute_output();
dec.print_out();
input.change_state(255);
dec.compute_output();
dec.print_out();
input.change_state(49);
dec.compute_output();
dec.print_out();

condition.change_state(7);
input.change_state(128);
dec.compute_output();
dec.print_out();
input.change_state(0);
dec.compute_output();
dec.print_out();
input.change_state(255);
dec.compute_output();
dec.print_out();
input.change_state(49);
dec.compute_output();
dec.print_out();

std::cout.rdbuf(old);
std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("0b0b0b0b0b0b1b0b1b1b0b0b") + 
					"1b1b1b0b1b1b1b1b1b0b1b1b" +
					"0b1b0b1b0b0b0b1b";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}


