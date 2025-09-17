/*****************************************
 * @file display_test.cpp
 *****************************************/
// Includes:
#include "display.hpp"
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace Virtual;

void print_as_raw(const std::string& s) {
    for (unsigned char c : s) {
        if (std::isprint(c)) {
            std::cout << c;              // printable as-is
        } else {
            std::cout << "\\x"             // escape non-printables
                      << std::setw(2)
                      << std::setfill('0')
                      << std::hex
                      << static_cast<int>(c);
        }
    }
    std::cout << std::dec; // reset formatting
}  

int main() {

std::ostringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
Switch_in save(false);
Switch_in flush(true);
WordSwitch_in input(11);

Display Dis( save.release_output(0), flush.release_output(0), input.release_word_output(0), 0.01);

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
std::string expectedOutput = R"(\x1b[?1049h\x1b[?25l\x1b[H11 \x0a11 77 \x0a11 77 0 3000 2999 222 \x0a)";
expectedOutput += R"(\x1b[H\xe2\x96\x88\xe2\x96\x80\xe2\x96\x84\xe2\x96\x88  \xe2\x96\x84                         \x0a   \xe2\x96\x84\xe2\x96\x84\xe2\x96\x84 \xe2\x96\x84\xe2\x96\x84\xe2\x96\x84 \xe2\x96\x84                    \x0a\xe2\x96\x80\xe2\x96\x88\xe2\x96\x88\xe2\x96\x84\xe2\x96\x88\xe2\x96\x80\xe2\x96\x84\xe2\x96\x88\xe2\x96\x80\xe2\x96\x80 \xe2\x96\x80                    \x0a)";

std::string capturedOutput = buffer.str();
std::ostringstream buffer2;
std::streambuf* old2 = std::cout.rdbuf(buffer2.rdbuf());
print_as_raw(capturedOutput);
std::cout.rdbuf(old2);
capturedOutput = buffer2.str();

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  // print_as_raw(capturedOutput);
  std::cout << std::endl;
  throw std::logic_error("Test failed!");
}

}		
