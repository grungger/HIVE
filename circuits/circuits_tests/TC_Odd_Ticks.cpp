#include "circuit.hpp"
#include "or.hpp"
#include "delay.hpp"
#include "not.cpp"
#define N_TICK 20
using namespace Virtual;

class Odd_Ticks_Circuit : public Circuit<1,0,1,0,3,1> {
  public:
    std::vector<std::vector<bool>> definitive_input;
    Odd_Ticks_Circuit(std::vector<bool> input_ticks={}) {
      if (input_ticks.empty()) {
        for (int i=0; i<N_TICK; i++) {
          definitive_input.push_back(std::vector<bool>(1,false));
        }
      }
      else {
        for (auto it=input_ticks.begin(); it!=input_ticks.end(); it++) {
          definitive_input.push_back(std::vector<bool>(1,*it));
        }
      }
      this->instantiate_in_out();
      input_pointers_[0] = bit_cin_[0]->release_output(0);
      circuit_components_[2] = std::make_shared<Delay>();
      circuit_components_[0] = std::make_shared<Not>(circuit_components_[2]->release_output(0));
      circuit_components_[1] = std::make_shared<Or>(circuit_components_[0]->release_output(0),
						    bit_cin_[0]->release_output(0));
      circuit_components_[2]->connect_input(circuit_components_[1]->release_output(0),0);
      output_pointers_[0] = circuit_components_[2]->release_output(0);
      memory_release_indices_[0] = 2;
      this->connect_couts();
    }
    void run() {
      this->run_script(definitive_input, std::vector<std::vector<std::uint8_t>>{});
    }
};


int main() {
  Odd_Ticks_Circuit circuit;
  circuit.run();
}
