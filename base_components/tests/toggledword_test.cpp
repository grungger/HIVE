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
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteSwitch_in byte_val(1);
Switch_in toggle_b(false);
ToggledByte byte(byte_val.release_byte_output(0), toggle_b.release_output(0));
byte.init();
byte.print_in(); // Expected: '0b1 '
byte.print_out(); // Expected: 'b0 '
byte.compute_output(); 
byte.print_out(); // Expected: 'b0 '
toggle_b.change_state(true); 
byte.compute_output(); 
byte.print_out(); // Expected: 'b1 '
byte_val.change_state(234);
byte.compute_output();
byte.print_out(); // Expected: 'b234 '

WordSwitch_in word_val(3333);
Switch_in toggle_w(true);
ToggledWord word(word_val.release_word_output(0), toggle_w.release_output(0));
word.init();
word.print_in(); // Expected: '1bw3333 '
word.print_out(); // Expected: 'bw0 '
word.compute_output();
word.print_out(); // Expected: 'bw3333 '
word_val.change_state(2);
toggle_w.change_state(false);
word.compute_output();
word.print_out(); // Expected: 'bw3333 '

WordSwitch_in word_val2(14);
Switch_in toggle_w2(true);
ToggledWord word2(word_val2.release_word_output(0), toggle_w2.release_output(0));
word2.init();
word2.connect_word_output(word.release_word_output(0));
word2.compute_output();
word.print_out(); // Expected: 'bw14 '

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "0b1 b0 b0 b1 b234 1bw3333 bw0 bw3333 bw3333 bw14 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}

