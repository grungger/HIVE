/*****************************************
 * @file display_test.cpp
 *****************************************/
// Includes:
#include "display.hpp"
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
Switch_in save(false);
Switch_in flush(true);
WordSwitch_in input(11);

Display Dis( save.release_output(0), flush.release_output(0), input.release_word_output(0), 5.0);

Dis.compute_output(); // expected: escape codes start
save.change_state(true);
flush.change_state(false);
Dis.compute_output();
Dis.printMemory(); // expected: "11 "
input.change_state(77);
Dis.compute_output();
Dis.printMemory(); // expected: "11 77 "
input.change_state(0);
Dis.compute_output();
input.change_state(3000);
Dis.compute_output();
input.change_state(2999);
Dis.compute_output();
input.change_state(222);
Dis.compute_output();
Dis.printMemory(); // expected: "11 77 0 3000 2999 222 "

save.change_state(false);
flush.change_state(true);
Dis.compute_output(); // expected: displayed memory
std::cout.rdbuf(old);

// Prediction:
std::string expectedOutput = u8"\x1b[?1049h\x1b[?25l11 11 77 11 77 0 3000 2999 222 ";
expectedOutput += "█▀▄█  ▄                         \n\
   ▄▄▄ ▄▄▄ ▄                    \n\
▀██▄█▀▄█▀▀ ▀                    \n";

std::string capturedOutput = buffer.str();


if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}		
