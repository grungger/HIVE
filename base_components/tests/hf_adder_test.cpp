/********************
 * @file hf_adder_test.cpp
 *
 * The test is called hf_adder_test can be built via "make hf_adder_test
 * and run via "make test" with all tests. It tests the functionality
 * of the HalfAdder and FullAdder circuit.
 ********************/
// Includes:
#include "switch_in.hpp"
#include "half_adder.hpp"
#include "full_adder.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in inA(false);
Switch_in inB(false);
Switch_in inC(false);

HalfAdder twobitadd(inA.release_output(0), inB.release_output(0));
FullAdder threebitadd(	inA.release_output(0),
			inB.release_output(0),
			inC.release_output(0));

twobitadd.print_out(); // Expected: 00
threebitadd.print_out(); // Expected: 00

inA.change_state(true);
twobitadd.compute_output();
threebitadd.compute_output();
twobitadd.print_out(); // Expected: 10
threebitadd.print_out(); // Expected: 10

inB.change_state(true);
twobitadd.compute_output();
threebitadd.compute_output();
twobitadd.print_out(); // Expected: 01
threebitadd.print_out(); // Expected: 01

inA.change_state(false);
twobitadd.compute_output();
threebitadd.compute_output();
twobitadd.print_out(); // Expected: 10
threebitadd.print_out(); // Expected: 10


inC.change_state(true);
inB.change_state(false);

threebitadd.print_out(); // Expected: 10

inA.change_state(true);
threebitadd.compute_output();
threebitadd.print_out(); // Expected: 01

inB.change_state(true);
threebitadd.compute_output();
threebitadd.print_out(); // Expected: 11

inA.change_state(false);
threebitadd.compute_output();
threebitadd.print_out(); // Expected: 01

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "000010100101101010011101";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}



