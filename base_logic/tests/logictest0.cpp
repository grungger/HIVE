/***********************
 * @file logictest0.cpp
 * 
 * The test is called io_test can be built via "make io_test" and
 *   run with all other tests via "make test". It tests Switch_in and
 *   Output functionality.
 ***********************/

#include "switch_in.hpp"
#include "output.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {
std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in input(true);
Output output(input.release_output(0));
input.print_in();
input.print_out();
output.print_in();
output.print_out();
output.compute_output();
input.change_state(false);
output.compute_output();
Output empty;
empty.compute_output();
std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "11100";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
