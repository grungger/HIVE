/****************************************
 * @file toggledword_test.cpp
 *
 * The test is called toggledword_test, can be built via
 * "make toggledword_test" and run via "make test". It tests
 * the functionality of ToggledByte and ToggledWord.
 ****************************************/
// Includes:
#include "toggledword.hpp"
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include "not.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteSwitch_in valA(0);
Switch_in tog(false);
ByteSwitch_in valB(0);
Not not_g(tog.release_output(0));
ToggledByte byteA(valA.release_byte_output(0), not_g.release_output(0));
byteA.init();
ToggledByte byteB(valB.release_byte_output(0),  tog.release_output(0));
byteB.init();
byteA.connect_byte_output(byteB.release_byte_output(0));
byteA.print_out(); // Expected: 'b0 '
byteB.print_out(); // Expected: 'b0 '
valA.change_state(27);
byteA.compute_output(); 
byteA.print_out(); // Expected: 'b27 '
byteB.print_in(); // Expected: '0b0 '
byteB.print_out(); // Expected: 'b27 '
byteB.compute_output();
byteA.print_out(); // Expected: 'b27 '
byteB.print_out();

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "b0 b0 b27 0b0 b27 b27 b27 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}

