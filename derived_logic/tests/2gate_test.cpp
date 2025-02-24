/*******************************************************
 * @file 2gate_test.cpp
 * 
 * The test is called 2gate_test can be built via "make 2gate_test" and
 *   run with all other tests via "make test". It tests all two bit gates,
 *   namely and, nand, nor, or, xor and xnor gate. It furthermore uses
 *   several Switch_in gates and it also uses a std::array of BaseGates 
 *   to test all gates together (hence testing BaseGate inheritance functionality).
 *******************************************************/

// Includes:
#include "switch_in.hpp"
#include "and.hpp"
#include "nand.hpp"
#include "nor.hpp"
#include "or.hpp"
#include "gate.hpp"
#include "xor.hpp"
#include "xnor.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <memory>

using namespace Virtual;

/**
 * @brief compute takes an array of gates and computes their output in order,
 *   while printing their output to std::ostream.
 */
void compute(std::array<std::shared_ptr<BaseGate>, 6> &gates) {
  for (auto it=gates.begin(); it<gates.end(); it++) {
    (*it)->compute_output();
    (*it)->print_out();
  }
}

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in inputA(false);
Switch_in inputB(false);

ptr_t inA_ptr = inputA.release_output(0);
ptr_t inB_ptr = inputB.release_output(0);

And and_gate(inA_ptr, inB_ptr);
NAND nand_gate(inA_ptr, inB_ptr);
Nor nor_gate(inA_ptr, inB_ptr);
Or or_gate(inA_ptr, inB_ptr);
Xor xor_gate(inA_ptr, inB_ptr);
Xnor xnor_gate(inA_ptr, inB_ptr);

std::array<std::shared_ptr<BaseGate>, 6> gates{ 
		std::make_shared<And>(and_gate),
		std::make_shared<NAND>(nand_gate),
		std::make_shared<Nor>(nor_gate),
		std::make_shared<Or>(or_gate),
		std::make_shared<Xor>(xor_gate),
		std::make_shared<Xnor>(xnor_gate) };

// false, false
// And 0, NAND 1, Nor 1, Or 0, Xor 0, Xnor 1
compute(gates); // Expected output: 011001

// false, true
inputB.change_state(true);
// And 0, NAND 1, Nor 0, Or 1, Xor 1, Xnor 0
compute(gates); // Expected output: 010110

// true, true
inputA.change_state(true);
// And 1, NAND 0, Nor 0, Or 1, Xor 0, Xnor 1
compute(gates); // Expected output: 100101

// true, false
inputB.change_state(false);
// And 0, NAND 1, Nor 0, Or 1, Xor 1, Xnor 0
compute(gates); // Expected output: 010110

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "011001010110100101010110";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
