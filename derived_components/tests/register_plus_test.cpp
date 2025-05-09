/*****************************************
 * @file register_plus_test.cpp
 *****************************************/
// Includes:
#include "register_plus.hpp"
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in save(false);
Switch_in load(false);
ByteSwitch_in b_val(0);

RegisterPlus b_mem( load.release_output(0), save.release_output(0),
			b_val.release_byte_output(0) );

b_mem.print_out(); // Expected: 'b0 0 '

b_mem.compute_output();
b_mem.print_out(); // Expected: 'b0 0 '

load.change_state(true);
b_mem.compute_output();
b_mem.print_out(); // Expected: 'b0 0 '

save.change_state(true);
load.change_state(false);
b_val.change_state(253);
b_mem.compute_output();
b_mem.print_out(); // Expected: 'b0 0 '

b_mem.memory_release();
b_mem.print_out(); // Expected: 'b0 253 '

load.change_state(true);
b_mem.compute_output();
b_mem.print_out(); // Expected: 'b253 253 '

b_val.change_state(1);
b_mem.compute_output();
b_mem.print_out(); // Expected: 'b253 253 '
b_mem.memory_release();
b_mem.print_out(); // Expected: 'b1 1 '

save.change_state(false);
load.change_state(false);
b_val.change_state(10);
b_mem.compute_output();
b_mem.print_out(); // Expected: 'b1 1 '

save.change_state(true);
load.change_state(true);
b_mem.compute_output();
b_mem.print_out(); // Expected: 'b1 1 '

save.change_state(false);
load.change_state(false);
b_mem.compute_output();
b_mem.print_out(); // Expected: 'b1 10 '
b_mem.memory_release();
b_mem.print_out(); // Expected: 'b1 10 '
load.change_state(true);
b_mem.memory_release();
b_mem.print_out(); // Expected: 'b10 10 '

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b0 0 b0 0 b0 0 b0 0 b0 253 ") +
					"b253 253 b253 253 b1 1 b1 1 " +
					"b1 1 b1 10 b1 10 b10 10 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}		
