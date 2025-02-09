#include "half_adder.hpp"

namespace Virtual{

HalfAdder::HalfAdder(ptr_t conA, ptr_t conB) {
  input_pointers_[0] = conA;
  input_pointers_[1] = conB;
  circuit_components_[0] = std::make_shared<Xor>(conA, conB);
  circuit_components_[1] = std::make_shared<And>(conA, conB);
  output_pointers_[0] = circuit_components_[0]->release_output(0);
  output_pointers_[1] = circuit_components_[1]->release_output(0);
}

void HalfAdder::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[0]->connect_input(input_pointers_[1],1);
  circuit_components_[1]->connect_input(input_pointers_[0],0);
  circuit_components_[1]->connect_input(input_pointers_[1],1);
}

const std::string HalfAdder::gate_name = "HalfAdder";

} //namespace Virtual
