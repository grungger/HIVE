/****************************
 * @file logictest1.cpp
 * 
 * The test is called nand_test, can be built via "make nand_test" and run
 *   with all other tests via "make test". It tests the NAND gate and also
 *   uses Switch_in gates.
 ****************************/

#include "switch_in.hpp"
#include "output.hpp"
#include "nand.hpp"

#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace Virtual;

int main() {
std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Switch_in inputA(false);
Switch_in inputB(false);

NAND nand_gate(inputA.release_output(0), inputB.release_output(0));

nand_gate.print_in();
nand_gate.print_out();
inputA.change_state(true);
nand_gate.compute_output();
nand_gate.print_out();

inputB.change_state(true);
inputA.change_state(false);
nand_gate.compute_output();
nand_gate.print_out();

inputA.change_state(true);
nand_gate.compute_output();
nand_gate.print_out();

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "001110";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}
