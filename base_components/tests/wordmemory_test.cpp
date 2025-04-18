/*****************************************
 * @file wordmemory_test.cpp
 * 
 * The test is called wordmemory_test, can be built via "make wordmemory_test"
 * and run via "make test" with all tests. It tests ByteMemory and WordMemory.
 *****************************************/
// Includes:
#include "word_memory.hpp"
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
WordSwitch_in w_val(0);

ByteMemory b_mem( load.release_output(0), save.release_output(0),
			b_val.release_byte_output(0) );
WordMemory w_mem( load.release_output(0), save.release_output(0),
			w_val.release_word_output(0) );

b_mem.print_out(); // Expected: 'b0 '
w_mem.print_out(); // Expected: 'bw0 '

b_mem.compute_output();
w_mem.compute_output();
b_mem.print_out(); // Expected: 'b0 '
w_mem.print_out(); // Expected: 'bw0 '

load.change_state(true);
b_mem.compute_output();
w_mem.compute_output();
b_mem.print_out(); // Expected: 'b0 '
w_mem.print_out(); // Expected: 'bw0 '

save.change_state(true);
load.change_state(false);
b_val.change_state(253);
w_val.change_state(257);
b_mem.compute_output();
w_mem.compute_output();
b_mem.print_out(); // Expected: 'b0 '
w_mem.print_out(); // Expected: 'bw0 '

b_mem.memory_release();
w_mem.memory_release();
b_mem.print_out(); // Expected: 'b0 '
w_mem.print_out(); // Expected: 'bw0 '

load.change_state(true);
b_mem.compute_output();
w_mem.compute_output();
b_mem.print_out(); // Expected: 'b253 '
w_mem.print_out(); // Expected: 'bw257 '

b_val.change_state(1);
w_val.change_state(2);
b_mem.compute_output();
w_mem.compute_output();
b_mem.print_out(); // Expected: 'b253 '
w_mem.print_out(); // Expected: 'bw257 '
b_mem.memory_release();
w_mem.memory_release();
b_mem.print_out(); // Expected: 'b1 '
w_mem.print_out(); // Expected: 'bw2 '

save.change_state(false);
load.change_state(false);
b_val.change_state(10);
w_val.change_state(20);
b_mem.compute_output();
w_mem.compute_output();
b_mem.print_out(); // Expected: 'b1 '
w_mem.print_out(); // Expected: 'bw2 '

save.change_state(true);
load.change_state(true);
b_mem.compute_output();
w_mem.compute_output();
b_mem.print_out(); // Expected: 'b1 '
w_mem.print_out(); // Expected: 'bw2 '

save.change_state(false);
load.change_state(false);
b_mem.compute_output();
w_mem.compute_output();
b_mem.print_out(); // Expected: 'b1 '
w_mem.print_out(); // Expected: 'bw2 '
b_mem.memory_release();
w_mem.memory_release();
b_mem.print_out(); // Expected: 'b1 '
w_mem.print_out(); // Expected: 'bw2 '
load.change_state(true);
b_mem.memory_release();
w_mem.memory_release();
b_mem.print_out(); // Expected: 'b10 '
w_mem.print_out(); // Expected: 'bw20 '

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b0 bw0 b0 bw0 b0 bw0 b0 bw0 b0 bw0 ") +
					"b253 bw257 b253 bw257 b1 bw2 b1 bw2 " +
					"b1 bw2 b1 bw2 b1 bw2 b10 bw20 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}		
