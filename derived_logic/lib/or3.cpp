#include "or3.hpp"

namespace Virtual{

Or3::Or3(ptr_t conA, ptr_t conB, ptr_t conC) {
  input_pointers_[0] = conA;
  input_pointers_[1] = conB;
  input_pointers_[2] = conC;
  circuit_components_[0] = std::make_shared<Or>(conA, conB);
  circuit_components_[1] = std::make_shared<Or>(circuit_components_[0]->release_output(0), conC);
  output_pointers_[0] = circuit_components_[1]->release_output(0);
}

void Or3::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0], 0);
  circuit_components_[0]->connect_input(input_pointers_[1], 1);
  circuit_components_[1]->connect_input(input_pointers_[2], 1);
}

const std::string Or3::gate_name = "Or(3)";

} //namespace Virtual
