#include "gate.hpp"
#ifndef MICROCIRCUIT_H
#define MICROCIRCUIT_H
namespace Virtual{

template <io_t N_in, io_t N_out, io_t N_comp>
class microCircuit : public Gate<N_in, N_out> {
  protected:
    std::array<std::shared_ptr<BaseGate>,N_comp> circuit_components_;
  public:
    void print_components() {
      for(auto it=circuit_components_.begin(); it<circuit_components_.end(); it++) {
        std::cout << (*it)->gate_name << std::endl;
      }
    }
    void connect_input(ptr_t connected_output, io_t index) {
      if (index >= N_in) {
        throw std::domain_error("Input that was attempted to connect is out of range");
      }
      this->input_pointers_[index] = connected_output;
      if (N_comp>=1) {
        rewire_input();
      }
    }
    virtual void rewire_input() {};
    void compute_output() {
      for(auto it=circuit_components_.begin(); it<circuit_components_.end(); it++) {
        (*it)->compute_output();
      }
    }
};

} //namespace Virtual

#endif
