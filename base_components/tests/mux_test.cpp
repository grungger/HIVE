#include "word_mux.hpp"
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in toggler(false);
ByteSwitch_in Bval1(33);
ByteSwitch_in Bval2(77);
WordSwitch_in val1(270);
WordSwitch_in val2(332);
ByteMUX bmux(
		toggler.release_output(0),
		Bval1.release_byte_output(0),
		Bval2.release_byte_output(0) );
WordMUX mux(
		toggler.release_output(0),
		val1.release_word_output(0),
		val2.release_word_output(0) );

bmux.compute_output();
mux.compute_output();

bmux.print_out(); // Expected: 'b33 '
mux.print_out(); // Expected: 'bw270 '

toggler.change_state(true);
bmux.compute_output();
mux.compute_output();
bmux.print_out(); // Expected: 'b77 '
mux.print_out(); // Expected: 'bw332 '

Bval2.change_state(1);
val2.change_state(3);
bmux.compute_output();
mux.compute_output();
bmux.print_out(); // Expected: 'b1 '
mux.print_out(); // Expected: 'bw3 '

ByteSwitch_in Bvalalt(25);
WordSwitch_in valalt(26);
bmux.connect_byte_input(Bvalalt.release_byte_output(0), 1);
mux.connect_word_input(valalt.release_word_output(0), 1);
bmux.compute_output();
mux.compute_output();
bmux.print_out(); // Expected: 'b25 '
mux.print_out(); // Expected: 'bw26 '

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b33 bw270 b77 bw332 b1 bw3 b25 bw26 ");

if(capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
