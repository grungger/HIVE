/******************************************
 * @file byte_decoder_test.cpp
 *
 * The test is called byte_decoder_test can be built via
 * "make byte_decoder_test" and run via "make test". It
 * tests the functionality of ByteDecoder and WordMakerByte.
 ******************************************/
// Includes:
#include "word_switch_in.hpp"
#include "byte_decoder.hpp"
#include "word_maker.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteSwitch_in in8A(0);
ByteDecoder decode(in8A.release_byte_output(0));
decode.print_out(); // expected: '1(0*255)b'

in8A.change_state(239);
decode.compute_output();
decode.print_out(); 

in8A.change_state(255);
decode.compute_output();
decode.print_out();

ByteSwitch_in in8B(3);
ByteSwitch_in in8C(0);
ByteSwitch_in in8D(0);
WordMakerByte make(in8A.release_byte_output(0),
			in8B.release_byte_output(0),
			in8C.release_byte_output(0),
			in8D.release_byte_output(0));
make.print_out(); // expected: 'bw1023 '

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput(771,'0');
expectedOutput[0] = '1';
expectedOutput[256] = 'b';
expectedOutput[496] = '1';
expectedOutput[513] = 'b';
expectedOutput[769] = '1';
expectedOutput[770] = 'b';
expectedOutput += "bw1023 ";
if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
