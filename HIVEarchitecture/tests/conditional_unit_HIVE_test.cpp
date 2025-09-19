/*********************************
 * @file conditional_unit_HIVE_test.cpp
 *********************************/
// Includes:
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include "ConditionalUnit.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in toggle(true);
ByteSwitch_in operation(0);
WordSwitch_in inputA(0);
WordSwitch_in inputB(0);
ConditionalUnitHIVE dec(
		toggle.release_output(0),
		operation.release_byte_output(0),
		inputA.release_word_output(0),
		inputB.release_word_output(0));
dec.print_out(); // expected: 1 
inputA.change_state(257); 
dec.compute_output();
dec.print_out(); // expected: 0
operation.change_state(1);
dec.compute_output();
dec.print_out(); // expected: 1
inputB.change_state(257);
dec.compute_output();
dec.print_out(); // expected: 0

operation.change_state(2);
dec.compute_output();
dec.print_out(); // expected: 1
inputA.change_state(16);
dec.compute_output();
dec.print_out(); // expected: 0
inputA.change_state(4294967295);
inputB.change_state(1);
dec.compute_output();
dec.print_out(); // expected: 1

operation.change_state(3);
dec.compute_output();
dec.print_out(); // expected: 1
inputA.change_state(192);
inputB.change_state(192);
dec.compute_output();
dec.print_out(); // expected: 0
inputA.change_state(191);
dec.compute_output();
dec.print_out(); // expected: 0

operation.change_state(4);
dec.compute_output();
dec.print_out(); // expected: 1
inputB.change_state(191);
dec.compute_output();
dec.print_out(); // expected: 1
inputB.change_state(7);
dec.compute_output();
dec.print_out(); // expected: 0

operation.change_state(5);
dec.compute_output();
dec.print_out(); // expected: 0
inputA.change_state(0);
dec.compute_output();
dec.print_out(); // expected: 1
inputA.change_state(7);
dec.compute_output();
dec.print_out(); // expected: 0

operation.change_state(6);
dec.compute_output();
dec.print_out(); // expected: 1
inputA.change_state(5500);
dec.compute_output();
dec.print_out(); // expected: 1
inputB.change_state(55001);
dec.compute_output();
dec.print_out(); // expected: 0
inputA.change_state(4294967295); // = -1
inputB.change_state(4294967200);  
dec.compute_output();
dec.print_out(); // expected: 1
inputA.change_state(2147483643);
inputB.change_state(2147483647);
dec.compute_output();
dec.print_out(); // expected: 0

operation.change_state(7);
dec.compute_output();
dec.print_out(); // expected: 0
operation.change_state(8);
dec.compute_output();
dec.print_out(); // expected: 1
operation.change_state(9);
dec.compute_output();
dec.print_out(); // expected: 1

operation.change_state(10);
inputA.change_state(128);
dec.compute_output();
dec.print_out(); // expected: 1
operation.change_state(11);
inputB.change_state(49);
dec.compute_output();
dec.print_out(); // expected: 0

std::cout.rdbuf(old);
std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("1bw0bw1bw0bw") + "1bw0bw1bw1bw0bw0bw" + "1bw1bw0bw0bw1bw0bw" + "1bw1bw0bw1bw0bw" + "0bw1bw1bw1bw0bw";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}


