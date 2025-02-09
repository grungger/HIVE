#include "full_adder.hpp"

namespace Virtual{

FullAdder::FullAdder(ptr_t conA, ptr_t conB, ptr_t conC) {
  input_pointers_[0] = conA;
  input_pointers_[1] = conB;
  input_pointers_[2] = conC;
  circuit_components_[0] = std::make_shared<HalfAdder>(conA,conB);
  circuit_components_[1] = std::make_shared<HalfAdder>(circuit_components_[0]->release_output(0), conC);
  circuit_components_[2] = std::make_shared<Or>(circuit_components_[0]->release_output(1), circuit_components_[1]->release_output(1));
  output_pointers_[0] = circuit_components_[1]->release_output(0);
  output_pointers_[1] = circuit_components_[2]->release_output(0);
}

void FullAdder::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[0]->connect_input(input_pointers_[1],1);
  circuit_components_[1]->connect_input(input_pointers_[2],1);
}

const std::string FullAdder::gate_name = "FullAdder";

} //namespace Virtual
