/*********************************
 * @file alu_HIVE_test.cpp
 *********************************/
// Includes:
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include "ArithmeticLogicUnit.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
Switch_in toggle(true);
ByteSwitch_in operation(0);
ByteSwitch_in carryRegister(0);
WordSwitch_in inputA(0);
WordSwitch_in inputB(0);
ALU_HIVE dec(
		toggle.release_output(0),
		operation.release_byte_output(0),
		carryRegister.release_byte_output(0),
		inputA.release_word_output(0),
		inputB.release_word_output(0));
dec.compute_output();
dec.print_out(); // expected: "b0 w4294967295 " 
inputA.change_state(1u<<16);
inputB.change_state((1u<<8)*128);
dec.compute_output();
dec.print_out(); // expected: "b0 w4294868991 "
operation.change_state(1);
dec.compute_output();
dec.print_out(); // expected: "b0 w0 "
inputB.change_state(257);
dec.compute_output();
dec.print_out(); // expected: "b0 w257 "

operation.change_state(2);
dec.compute_output();
dec.print_out(); // expected: "b0 w4294967038 "
inputA.change_state(272);
dec.compute_output();
dec.print_out(); // expected: "b0 w4294967039 "
inputA.change_state(4294967295);
inputB.change_state(22222);
dec.compute_output();
dec.print_out(); // expected: "b0 w4294945073 "

operation.change_state(3);
inputA.change_state(5);
inputB.change_state(50);
dec.compute_output();
dec.print_out(); // expected: "b0 w55 "
inputA.change_state(192);
inputB.change_state(15);
dec.compute_output();
dec.print_out(); // expected: "b0 w207 "
inputA.change_state(191);
dec.compute_output();
dec.print_out(); // expected: "b0 w191 "

operation.change_state(4);
dec.compute_output();
dec.print_out(); // expected: "b0 w4294967104 "
inputB.change_state(167772160);
dec.compute_output();
dec.print_out(); // expected: "b0 w4127194944 "
inputB.change_state(64);
dec.compute_output();
dec.print_out(); // expected: "b0 w4294967040 "

operation.change_state(5);
inputB.change_state(250);
dec.compute_output();
dec.print_out(); // expected: "b0 w69 "
inputA.change_state(0);
dec.compute_output();
dec.print_out(); // expected: "b0 w250 "
inputA.change_state(7);
dec.compute_output();
dec.print_out(); // expected: "b0 w253 "

operation.change_state(6);
dec.compute_output();
dec.print_out(); // expected: "b0 w5 "
inputA.change_state(5500);
dec.compute_output();
dec.print_out(); // expected: "b0 w5380 "
inputA.change_state(5501);
dec.compute_output();
dec.print_out(); // expected: "b0 w5381 "
inputA.change_state(4294967295); // = -1
inputB.change_state(4294967200);  
dec.compute_output();
dec.print_out(); // expected: "b0 w95 "
inputA.change_state(2147483643);
inputB.change_state(2147483628);
dec.compute_output();
dec.print_out(); // expected: "b0 w19 "

operation.change_state(7);
dec.compute_output();
dec.print_out(); // expected: "b0 w4294967271 "
inputA.change_state(4294967295);
inputB.change_state(14);
dec.compute_output();
dec.print_out(); // expected: "b1 w13 "
operation.change_state(8);
dec.compute_output();
dec.print_out(); // expected: "b1 w13 "
carryRegister.change_state(1);
dec.compute_output();
dec.print_out(); // expected: "b1 w14 "
operation.change_state(9);
dec.compute_output();
dec.print_out(); // expected: "b1? w4294967281 "

operation.change_state(10);
inputA.change_state(128);
dec.compute_output();
dec.print_out(); // expected: "b1 w114 "
operation.change_state(11);
inputB.change_state(49);
dec.compute_output();
dec.print_out(); // expected: "b1 w4294967217 "

operation.change_state(12);
dec.compute_output();
dec.print_out(); // expected: "b1 w4294967217 "
operation.change_state(13);
inputA.change_state(15);
inputB.change_state(2);
dec.compute_output();
dec.print_out(); // expected: "b0 w3 "
inputA.change_state(4294967295);
dec.compute_output();
dec.print_out(); // expected: "b0 w4294967295 "
operation.change_state(14);
dec.compute_output();
dec.print_out(); // expected: "b0 w2684354559 "
operation.change_state(15);
inputA.change_state(13);
inputB.change_state(5);
dec.compute_output();
dec.print_out(); // expected: "b0 w416 "


std::cout.rdbuf(old);
std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b0 w4294967295 b0 w4294868991 b0 w0 b0 w257 b0 w4294967038 b0 w4294967039 ") +
       					"b0 w4294945073 b0 w55 b0 w207 b0 w191 b0 w4294967104 b0 w4127194944 b0 w4294967040 " +
					"b0 w69 b0 w250 b0 w253 b0 w5 b0 w5380 b0 w5381 b0 w95 b0 w19 b0 w4294967271 " + 
					"b1 w13 b1 w13 b1 w14 b1 w4294967281 " + // ?last b1?
					"b1 w114 b1 w4294967217 b1 w4294967217 b1 w3 b1 w4294967295 b1 w1073741823 b1 w416 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}


