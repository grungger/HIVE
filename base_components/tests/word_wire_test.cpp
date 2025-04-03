/************************************************
 * @file word_wire_test.cpp
 * 
 * The test is called word_wire_test can be built via "make word_wire_test" and run
 * via "make test". It tests the functionality of ByteWire and WordWire.
 ************************************************/
// Includes:
#include "word_wire.hpp"
#include "word_switch_in.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteSwitch_in in8(131);
WordSwitch_in in32(4101); // 4096(2^12) + 4 + 1

ByteWire wire(in8.release_byte_output(0));
WordWire wwire(in32.release_word_output(0));
wire.print_out(); // expected: 'b131 '
wwire.print_out(); // expected: 'bw4101 '

ByteSwitch_in in8_re(2);
WordSwitch_in in32_re(3);
ByteWire wire_re(in8_re.release_byte_output(0), wire.release_byte_output(0));
WordWire wwire_re(in32_re.release_word_output(0), wwire.release_word_output(0));
wire_re.compute_output();
wwire_re.compute_output();

wire.print_out(); // expected: 'b2 '
wwire.print_out(); // expected: 'bw3 '
wire_re.print_out(); // expected: 'b2 '
wwire_re.print_out(); // expected: 'bw3 '

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "b131 bw4101 b2 bw3 b2 bw3 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
