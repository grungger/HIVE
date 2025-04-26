/*******************************************************
 * @file counter_test.cpp
 *
 * @brief The test is called counter_test, can be built 
 *   via "make counter_test" and run via "make test", it
 *   tests the functionality of ByteCounter & Counter.
 *******************************************************/
// Includes:
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include "counter.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in overwrite(false);
ByteSwitch_in Bvalue(0);
WordSwitch_in value(0);
ByteCounter Bcounter(
		overwrite.release_output(0),
		Bvalue.release_byte_output(0) );
Bcounter.init();
Counter counter(
		overwrite.release_output(0),
		value.release_word_output(0) );
counter.init();

Bcounter.print_out(); // Expected: 'b0 '
Counter.print_out(); // Expected: 'bw0 '

Bcounter.compute_output();
Counter.compute_output();

Bcounter.print_out(); // Expected: 'b


std::cout.rdbuf(old);
std::string capturedOutput = buffer.str();
std::string expectedOutput = "";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
