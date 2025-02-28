/**********************************
 * @file toggledbit_test.cpp
 *
 * The test is called toggledbit_test, can be built via "make toggledbit_test" and
 * run via "make test" with all tests. It tests the functionality of the
 * ToggledBit microCircuit.
 **********************************/
// Includes:
#include "toggledbit.hpp"
#include "switch_in.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in value(false);
Switch_in toggle(false);

ToggledBit bit(value.release_output(0), toggle.release_output(0));
bit.print_in(); // Expected: 00
bit.print_out(); // Expected: 0

bit.compute_output();
bit.print_out(); // Expected: 0

value.change_state(true);
bit.compute_output();
bit.print_in(); // Expected: 10
bit.print_out(); // Expected: 0

toggle.change_state(true);
value.change_state(false);
bit.compute_output();
bit.print_in(); // Expected: 01
bit.print_out(); // Expected: 0

value.change_state(true);
bit.compute_output();
bit.print_in(); // Expected: 11
bit.print_out(); // Expected: 1

bit.compute_output();
bit.print_in(); // Expected: 11
bit.print_out(); // Expected: 1

toggle.change_state(false);
bit.compute_output();
bit.print_in(); // Expected: 10
bit.print_out(); // Expected: 1

value.change_state(false);
bit.compute_output();
bit.print_in(); // Expected: 00
bit.print_out(); // Expected: 1

Switch_in value2(false);
Switch_in toggle2(false);
ToggledBit bit2(value2.release_output(0), toggle2.release_output(0));
bit2.connect_output(bit.release_output(0));

bit2.compute_output();
bit2.print_out(); // Expected: 1

toggle2.change_state(true);
bit.compute_output();
bit2.compute_output();
bit.print_out(); // Expected: 0

value.change_state(true);
toggle.change_state(true);
bit.compute_output();
bit2.print_out(); // Expected: 1

bit.compute_output();
bit2.compute_output();
bit.print_out(); // Expected: 0
bit2.print_out(); // Expected: 0

bit2.compute_output();
bit.compute_output();
bit.print_out(); // Expected: 1
bit2.print_out(); // Expected: 1


std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "00001000101111111010011010011";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
