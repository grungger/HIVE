/******************************************
 * @file split_combine_test.cpp
 *
 * The test is called split_combine_test can be built via
 * "make split_combine_test" and run via "make test". It
 * tests the functionality of ByteSwitch_in, WordSwitch_in,
 * ByteSplitter, WordSplitter, ByteMaker, WordMaker,
 * ByteOutput and WordOutput.
 ******************************************/
// Includes:
#include "word_switch_in.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "word_output.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteSwitch_in in8A(7);
ByteSplitter split(in8A.release_byte_output(0));
split.print_out(); // expected: '11100000b'
ByteMaker make(split.release_bytearg_output());
make.print_out(); // expected: 'b7 '
ByteMaker doubler(Gate<0,0>::ground,
		split.release_output(0),
		split.release_output(1),
		split.release_output(2),
		split.release_output(3),
		split.release_output(4),
		split.release_output(5),
		split.release_output(6) );
doubler.print_out(); // expected: 'b14 '

in8A.change_state(239);
split.compute_output();
split.print_out(); // expected: '11110111b'
make.compute_output();
make.print_out(); // expected: 'b239 '
doubler.compute_output();
doubler.print_out(); // expected: 'b222 '

WordSwitch_in in32A(256);
WordSplitter splitword(in32A.release_word_output(0));
splitword.print_out(); // expected: '00000000100000000000000000000000bw'
WordMaker makeword(splitword.release_wordarg_output());
makeword.print_out(); // expected: 'bw256 '
WordArg splitter_out = splitword.release_wordarg_output();
splitter_out.bits[2] = splitter_out.bits[8]; // add 2 to output
WordMaker makewordadd2(splitter_out);
makewordadd2.print_out(); // expected: 'bw260 '

in32A.change_state(2147483904); // bit 32 and bit 9 turned on
splitword.compute_output();
splitword.print_out(); // expected: '00000000100000000000000000000001bw'
makeword.compute_output();
makeword.print_out(); // expected: 'bw2147483904 '
makewordadd2.compute_output();
makewordadd2.print_out(); // expected: 'bw2147483908 '

ByteOutput byteout(make.release_byte_output(0));
byteout.compute_output(); // expected: '239'
byteout.printf_out(); // expected: 'ByteOutput 0: 239\n'
WordOutput wordout(makeword.release_word_output(0));
wordout.compute_output(); // expected: '2147483904' 
wordout.printf_out(); // expected: 'WordOutput 0: 2147483904\n'

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("11100000bb7 b14 11110111bb239 b222 ") +
			     "00000000100000000000000000000000bwbw256 bw260 " +
			     "00000000100000000000000000000001bwbw2147483904 bw2147483908 " +
			     "239ByteOutput 0: 239\n2147483904WordOutput 0: 2147483904\n";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
