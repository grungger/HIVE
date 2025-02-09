#include "switch_in.hpp"
#include "output.hpp"
#include "and.hpp"
#include "nand.hpp"
#include "nor.hpp"
#include "or.hpp"
#include "gate.hpp"
#include "xor.hpp"
#include "xnor.hpp"
#include <memory>
#define N_TEST 6

using namespace Virtual;

void compute(std::array<std::shared_ptr<BaseGate>,N_TEST> &gates, std::array<std::shared_ptr<Output>,N_TEST> &outs) {
  for (auto it=gates.begin(); it< gates.end(); it++) {
    (*it)->compute_output();
  }
  for (auto it=outs.begin();it<outs.end();it++) {
    (*it)->compute_output();
  } 
}

int main() {

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

Output out_and(and_gate.release_output(0));
Output out_nand(nand_gate.release_output(0));
Output out_nor(nor_gate.release_output(0));
Output out_or(or_gate.release_output(0));
Output out_xor(xor_gate.release_output(0));
Output out_xnor(xnor_gate.release_output(0));

std::cout << "Output 0 = And" << std::endl;
std::cout << "Output 1 = Nand" << std::endl;
std::cout << "Output 2 = Nor" << std::endl;
std::cout << "Output 3 = Or" << std::endl;
std::cout << "Output 4 = Xor" << std::endl;
std::cout << "Output 5 = Xnor" << std::endl;

std::array<std::shared_ptr<BaseGate>,N_TEST> gates{std::make_shared<And>(and_gate),std::make_shared<NAND>(nand_gate),std::make_shared<Nor>(nor_gate),std::make_shared<Or>(or_gate),std::make_shared<Xor>(xor_gate),std::make_shared<Xnor>(xnor_gate)};

std::array<std::shared_ptr<Output>,N_TEST> outs{std::make_shared<Output>(out_and), std::make_shared<Output>(out_nand), std::make_shared<Output>(out_nor),std::make_shared<Output>(out_or),std::make_shared<Output>(out_xor),std::make_shared<Output>(out_xnor)};

std::cout << "false, false: " << std::endl;
compute(gates,outs);

std::cout << "true, false: " << std::endl;
inputA.change_state(true);
compute(gates,outs);

std::cout << "false, true: " << std::endl;
inputA.change_state(false);
inputB.change_state(true);
compute(gates,outs);

std::cout << "true, true: " << std::endl;
inputA.change_state(true);
compute(gates,outs);

}
