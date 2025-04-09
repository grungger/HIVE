/*****************************************
 * @file bitwise_op_test.cpp
 *
 * The test is called bitwise_op_test, can be built 
 * via "make bitwise_op_test" and run via "make test".
 * It tests the functionality of Adder, And, for Byte and Word. 
 */
// Includes:
#include "word_adder.hpp"
#include "word_switch_in.hpp"
#include "switch_in.hpp"
#include "word_and.hpp"
#include "word_mux.hpp"
#include "word_nand.hpp"
#include "word_nor.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in inbit(false);
ByteSwitch_in inA(0);
ByteSwitch_in inB(0);

ByteAdder b_add(inbit.release_output(0), 
		inA.release_byte_output(0), inB.release_byte_output(0));
ByteAnd b_and(inA.release_byte_output(0), inB.release_byte_output(0));
ByteMUX b_mux(inbit.release_output(0),
		inA.release_byte_output(0), inB.release_byte_output(0));
ByteNAND b_nand(inA.release_byte_output(0), inB.release_byte_output(0));
ByteNor b_nor(inA.release_byte_output(0), inB.release_byte_output(0));

b_add.print_out(); // Expected: '0b0 '
b_and.print_out(); // Expected: 'b0 '
b_mux.print_out();  //  Expected: 'b0 '
b_nand.print_out(); // Expected: 'b255 '
b_nor.print_out(); // Expected: 'b255 '

inA.change_state(27); // 16 8 2 1
b_add.compute_output();
b_and.compute_output();
b_mux.compute_output();
b_nand.compute_output();
b_nor.compute_output(); // 128 64 32 4

b_add.print_out(); // Expected: '0b27 '
b_and.print_out(); // Expected: 'b0 '
b_mux.print_out(); // Expected: 'b27 '
b_nand.print_out(); // Expected: 'b255 '
b_nor.print_out(); // Expected: 'b228 '

inB.change_state(22); // 16 4 2
b_add.compute_output();
b_and.compute_output();
b_mux.compute_output();
b_nand.compute_output(); // 128 64 32 8 4 1 = 237
b_nor.compute_output(); // 128 64 32

b_add.print_out(); // Expected: '0b49 '
b_and.print_out(); // Expected: 'b18 '
b_mux.print_out(); // Expected: 'b27 '
b_nand.print_out(); // Expected: 'b237 '
b_nor.print_out(); // Expected: 'b224 '

inbit.change_state(true);
inA.change_state(255);
b_add.compute_output();
b_and.compute_output();
b_mux.compute_output();
b_nand.compute_output(); // 255 - 22 = 233
b_nor.compute_output(); 

b_add.print_out(); // Expected: '1b22 '
b_and.print_out(); // Expected: 'b22 '
b_mux.print_out(); // Expected: 'b22 '
b_nand.print_out(); // Expected: 'b233 '
b_nor.print_out(); // Expected: 'b0 '

Switch_in inbit2(false);
WordSwitch_in inwA(0);
WordSwitch_in inwB(0);

WordAdder w_add(inbit2.release_output(0),
		inwA.release_word_output(0), inwB.release_word_output(0));
WordAnd w_and(inwA.release_word_output(0),  inwB.release_word_output(0));
WordMUX w_mux(inbit2.release_output(0),
		inwA.release_word_output(0), inwB.release_word_output(0));
WordNAND w_nand(inwA.release_word_output(0), inwB.release_word_output(0));
WordNor w_nor(inwA.release_word_output(0), inwB.release_word_output(0));

w_add.print_out(); //  Expected: '0bw0 '
w_and.print_out(); // Expected: 'bw0 '
w_mux.print_out(); // Expected: 'bw0 '
w_nand.print_out(); // Expected: 'bw4294967295 '
w_nor.print_out(); // Expected: 'bw4294967295 '

inwA.change_state(19); // 16 2 1
w_add.compute_output();
w_and.compute_output();
w_mux.compute_output();
w_nand.compute_output();
w_nor.compute_output();

w_add.print_out(); // Expected: '0bw19 '
w_and.print_out(); // Expected: 'bw0 '
w_mux.print_out(); // Expected: 'bw19 '
w_nand.print_out(); // Expected: 'bw4294967295 '
w_nor.print_out(); // Expected: 'bw4294967276 '

inwB.change_state(3); // 2 1
w_add.compute_output();
w_and.compute_output();
w_mux.compute_output();
w_nand.compute_output(); // max - 2 1
w_nor.compute_output();

w_add.print_out(); // Expected: '0bw22 '
w_and.print_out(); // Expected: 'bw3 '
w_mux.print_out(); // Expected: 'bw19 '
w_nand.print_out(); // Expected: 'bw4294967292 '
w_nor.print_out(); // Expected: 'bw4294967276 '

inbit2.change_state(true);
inwA.change_state(4294967294); // max - 1
w_add.compute_output();
w_and.compute_output();
w_mux.compute_output();
w_nand.compute_output(); // max - 2
w_nor.compute_output();

w_add.print_out(); // Expected: '1bw1 '
w_and.print_out(); // Expected: 'bw2 '
w_mux.print_out(); // Expected: 'bw3 '
w_nand.print_out(); // Expected: 'bw4294967293 '
w_nor.print_out(); // Expected: 'bw0 '

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("0b0 b0 b0 b255 b255 0b27 b0 b27 b255 b228 ") + 
					"0b49 b18 b27 b237 b224 1b22 b22 b22 b233 b0 " + 
					"0bw0 bw0 bw0 bw4294967295 bw4294967295 " + 
					"0bw19 bw0 bw19 bw4294967295 bw4294967276 " + 
					"0bw22 bw3 bw19 bw4294967292 bw4294967276 " + 
					"1bw2 bw2 bw3 bw4294967293 bw0 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
