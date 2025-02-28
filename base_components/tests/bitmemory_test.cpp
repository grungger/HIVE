/********************************
 * @file bitmemory_test.cpp
 * 
 * The test is called bitmemory_test, can be built via "make bitmemory_test" and
 * run via "make test" with all tests. It tests the functionality of BitMemory.
 ********************************/
// Includes:
#include "bitmemory.hpp"
#include "switch_in.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in save_tog(false);
Switch_in save_val(false);

BitMemory mem(save_tog.release_output(0), save_val.release_output(0));
mem.print_out(); // Expected: 0

// in: 00
mem.compute_output();
mem.print_out(); // Expected: 0

// in: 01
save_val.change_state(true);
mem.compute_output();
mem.print_out(); // Expected: 0

// in: 11
save_tog.change_state(true);
mem.compute_output();
mem.print_out(); // Expected: 0

// in: 00
save_tog.change_state(false);
save_val.change_state(false);
mem.compute_output();
mem.print_out(); // Expected: 1

// in: 00
mem.compute_output();
mem.print_out(); // Expected: 1

// in: 00
mem.compute_output();
mem.print_out(); // Expected: 1

// in: 11
save_tog.change_state(true);
save_val.change_state(true);
mem.compute_output();
mem.print_out(); // Expected: 1

// in: 01
save_val.change_state(false);
mem.compute_output();
mem.print_out(); // Expected: 1

// in: 00
save_tog.change_state(false);
mem.compute_output();
mem.print_out(); // Expected: 0

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "0000111110";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
