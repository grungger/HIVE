#include "circuit.hpp"
#include "bitmemory.hpp"
#include <iostream>

using namespace Virtual;

class SavingBitsCircuit : public Circuit<2,0,1,0,1,0> {
  public:
    std::vector<std::vector<bool>> definitive_input;
    SavingBitsCircuit(std::vector<bool> save_ens, std::vector<bool> save_vals) {
      for (unsigned long i=0; i<save_ens.size(); i++) {
        definitive_input.push_back(std::vector<bool>{save_ens[i],save_vals[i]});
      }
      this->instantiate_in_out();
      input_pointers_[0] = bit_cin_[0]->release_output(0);
      input_pointers_[1] = bit_cin_[1]->release_output(0);
      circuit_components_[0] = std::make_shared<BitMemory>(bit_cin_[0]->release_output(0),
							bit_cin_[1]->release_output(0));
      output_pointers_[0] = circuit_components_[0]->release_output(0);
      this->connect_couts();
    }
    void run() {
      this->run_script(definitive_input, std::vector<std::vector<std::uint8_t>>{});
    }
};

int main() {
  SavingBitsCircuit circuit(std::vector<bool>{1,1,1,1,0,0,1,1,1,0,0,1,1},
			std::vector<bool>{1,1,0,0,0,1,0,1,1,1,0,0,0});
  std::cout<<"Expected output: " << std::endl;
  std::cout << "0 1 1 0 0 0 0 0 1 1 1 1 0" << std::endl;
  circuit.run();
  std::cout << std::endl;
}
