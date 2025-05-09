/*********************************
 * @file arithmetic_logic_unit_test.cpp
 *********************************/
// Includes:
#include "word_switch_in.hpp"
#include "arithmetic_logic_unit.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteSwitch_in instruction(0);
ByteSwitch_in inputA(0);
ByteSwitch_in inputB(10);
ArithmeticLogicUnit dec(instruction.release_byte_output(0),
			inputA.release_byte_output(0),
			inputB.release_byte_output(0));
dec.compute_output();
dec.print_out(); // E: b10 
inputA.change_state(16); 
dec.compute_output();
dec.print_out(); // E: b26
inputA.change_state(3);
dec.compute_output();
dec.print_out(); // E: b11
inputB.change_state(96);
dec.compute_output();
dec.print_out(); // E: b99

instruction.change_state(1);
inputB.change_state(8);
dec.compute_output();
dec.print_out(); // E: b255
inputA.change_state(255);
dec.compute_output();
dec.print_out(); // E: b247
inputB.change_state(200);
dec.compute_output();
dec.print_out(); // E: b55
inputA.change_state(56);
dec.compute_output();
dec.print_out(); // E: b247

instruction.change_state(2);
inputB.change_state(128);
dec.compute_output();
dec.print_out(); // E: b71
inputA.change_state(3);
dec.compute_output();
dec.print_out(); // E: b124
inputB.change_state(255);
dec.compute_output();
dec.print_out(); // E: b0
inputB.change_state(251);
dec.compute_output();
dec.print_out(); // E: b4

instruction.change_state(3);
inputA.change_state(128);
dec.compute_output();
dec.print_out(); // E: b128
inputB.change_state(127);
dec.compute_output();
dec.print_out(); // E: b0
inputA.change_state(183);
dec.compute_output();
dec.print_out(); // E: b55
inputB.change_state(49);
dec.compute_output();
dec.print_out(); // E: b49

instruction.change_state(4);
inputA.change_state(128);
dec.compute_output();
dec.print_out(); // E: b177
inputB.change_state(5);
dec.compute_output();
dec.print_out(); // E: b133
inputA.change_state(253);
dec.compute_output();
dec.print_out(); // E: b2
inputB.change_state(49);
dec.compute_output();
dec.print_out(); // E: b46

instruction.change_state(5);
inputA.change_state(12);
dec.compute_output();
dec.print_out(); // E: b219
inputA.change_state(0);
dec.compute_output();
dec.print_out(); // E: b207
inputA.change_state(59);
inputB.change_state(255);
dec.compute_output();
dec.print_out(); // E: b60
inputB.change_state(49);
dec.compute_output();
dec.print_out(); // E: b10

std::cout.rdbuf(old);
std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b10 b26 b11 b99 b255 b247 ") +
       					"b55 b247 b71 b124 b0 b4 b128 " +
					"b0 b55 b49 b177 b133 b2 b46 " +
					"b219 b207 b60 b10 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}


