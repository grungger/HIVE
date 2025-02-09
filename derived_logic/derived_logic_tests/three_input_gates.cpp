#include "switch_in.hpp"
#include "output.hpp"
#include "and3.hpp"
#include "or3.hpp"

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

Output out_and(and_gate.release_output(0));
Output out_or(or_gate.release_output(0));

std::cout << "and(false, false, false)" << std::endl;
out_and.compute_output();
out_or.compute_output();

std::cout << "and(false, false, true)" << std::endl;
inC.change_state(true);
and_gate.compute_output();
or_gate.compute_output();
out_and.compute_output();
out_or.compute_output();

std::cout << "and(false, true, true)" << std::endl;
inB.change_state(true);
and_gate.compute_output();
or_gate.compute_output();
out_and.compute_output();
out_or.compute_output();

std::cout << "and(true, true, true)" << std::endl;
inA.change_state(true);
and_gate.compute_output();
or_gate.compute_output();
out_and.compute_output();
out_or.compute_output();

}
