/********************************************************
 * @file 3gate_test.cpp
 *
 * The test is called 3gate_test, can be built via "make 3gate_test" and
 *   run with all other tests via "make test". It tests all three bit gates,
 *   And3 gate and Or3 gate.
 ********************************************************/
// Includes:
#include "switch_in.hpp"
#include "and3.hpp"
#include "or3.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {

Switch_in inA(false);
Switch_in inB(false);
Switch_in inC(false);

ptr_t conA = inA.release_output(0);
ptr_t conB = inB.release_output(0);
ptr_t conC = inC.release_output(0);

And3 and_gate(conA, conB, conC);
Or3 or_gate(conA, conB, conC);

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

// false, false, false
and_gate.compute_output();
and_gate.print_out();
or_gate.compute_output();
or_gate.print_out();
// Expected: 00

// false, false, true
inC.change_state(true);
and_gate.compute_output();
and_gate.print_out();
or_gate.compute_output();
or_gate.print_out();
// Expected: 01

// false, true, true
inB.change_state(true);
and_gate.compute_output();
and_gate.print_out();
or_gate.compute_output();
or_gate.print_out();
// Expected: 01

// false, true, false
inC.change_state(false);
and_gate.compute_output();
and_gate.print_out();
or_gate.compute_output();
or_gate.print_out();
// Expected: 01

// true, true, false
inA.change_state(true);
and_gate.compute_output();
and_gate.print_out();
or_gate.compute_output();
or_gate.print_out();
// Expected: 01

// true, false, false
inB.change_state(false);
and_gate.compute_output();
and_gate.print_out();
or_gate.compute_output();
or_gate.print_out();
// Expected: 01

// true, false, true
inC.change_state(true);
and_gate.compute_output();
and_gate.print_out();
or_gate.compute_output();
or_gate.print_out();
// Expected: 01

// true, true, true
inB.change_state(true);
and_gate.compute_output();
and_gate.print_out();
or_gate.compute_output();
or_gate.print_out();
// Expected: 11

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "0001010101010111";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
