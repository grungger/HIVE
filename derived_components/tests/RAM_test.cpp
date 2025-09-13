/*****************************************
 * @file RAM_test.cpp
 *****************************************/
// Includes:
#include "RAM.hpp"
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include <sstream>
#include <iostream>
#include <cmath>

using namespace Virtual;

int main() {

// std::stringstream buffer;
// std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

WordSwitch_in full_opcode(std::pow(2,24)+std::pow(2,25)+std::pow(2,30));
WordSwitch_in value(33);
RAM RAM_comp(   
		full_opcode.release_word_output(0),
		value.release_word_output(0) );
RAM_comp.print_out(); // Expected: 'b0 0 '
RAM_comp.printRAM();
RAM_comp.compute_output();
std::cout << "\n";
RAM_comp.printRAM();
RAM_comp.print_out();
RAM_comp.compute_output();
RAM_comp.printRAM();
//RAM_comp.print_out(); // Expected: 'b0 0 '


// std::cout.rdbuf(old);

std::string capturedOutput = std::string(" "); // buffer.str();
std::string expectedOutput = std::string("b0 0 b0 0 b0 0 b0 0 b0 253 ") +
					"b253 253 b253 253 b1 1 b1 1 " +
					"b1 1 b1 10 b1 10 b10 10 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}		
