#include "not.hpp"

namespace Virtual{

Not::Not(ptr_t connected) {
  input_pointers_[0] = connected;
  circuit_components_[0] = std::make_shared<NAND>(connected,connected);
  output_pointers_[0] = circuit_components_[0]->release_output(0);
}

void Not::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[0]->connect_input(input_pointers_[0],1);
}

const std::string Not::gate_name = "Not";

} //namespace Virtual
