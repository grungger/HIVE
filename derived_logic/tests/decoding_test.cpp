/***********************************
 * @file decoding_test.cpp
 *
 * The test is called decoding_test, can be built via "make decoding_test" and
 *   run via "make test" with all tests. It tests the functionality of the
 *   OneBitDecoder and the ThreeBitDecoder, using several Switch_in inputs.
 ***********************************/
// Includes:
#include "onebitdecoder.hpp"
#include "threebitdecoder.hpp"
#include "switch_in.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

// 1bit decoder test:

Switch_in input(false);

OneBitDecoder onedecoder(input.release_output(0));
onedecoder.print_out();

input.change_state(true);
onedecoder.compute_output();
onedecoder.print_out();

// 3bit decoder test:

Switch_in input1(false);
Switch_in input2(false);
Switch_in input4(false);

ThreeBitDecoder threedecoder(	input1.release_output(0),
				input2.release_output(0),
				input4.release_output(0));

// Decoded 0 = 10000000
threedecoder.compute_output();
threedecoder.print_out();

// Decoded 1 = 01000000
input1.change_state(true);
threedecoder.compute_output();
threedecoder.print_out();

// Decoded 3 = 00010000
input2.change_state(true);
threedecoder.compute_output();
threedecoder.print_out();

// Decoded 7 = 00000001
input4.change_state(true);
threedecoder.compute_output();
threedecoder.print_out();

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "100110000000010000000001000000000001";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
