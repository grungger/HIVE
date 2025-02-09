#include "switch_in.hpp"
#include "output.hpp"
#include "nand.hpp"

using namespace Virtual;

int main() {

Switch_in inputA(false);
Switch_in inputB(false);

ptr_t connectorA = inputA.release_output(0);
ptr_t connectorB = inputB.release_output(0);

NAND nand_gate(connectorA, connectorB);
ptr_t connector = nand_gate.release_output(0);
std::cout << nand_gate.gate_name << " inputs: ";
nand_gate.print_in();
std::cout << std::endl;
std::cout << nand_gate.gate_name << " outputs: ";
nand_gate.print_out();
std::cout << std::endl;

Output output(connector);

output.compute_output();

inputA.change_state(true);
nand_gate.compute_output();
output.compute_output();

inputB.change_state(true);
nand_gate.compute_output();
output.compute_output();

}
