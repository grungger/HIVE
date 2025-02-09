#include "and3.hpp"

namespace Virtual{

And3::And3(ptr_t conA, ptr_t conB, ptr_t conC) { 
  input_pointers_[0] = conA;
  input_pointers_[1] = conB;
  input_pointers_[2] = conC;
  circuit_components_[0] = std::make_shared<And>(conA,conB);
  circuit_components_[1] = std::make_shared<And>((circuit_components_[0]->release_output(0)), conC);
  output_pointers_[0] = circuit_components_[1]->release_output(0);
}

void And3::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[0]->connect_input(input_pointers_[1],1);
  circuit_components_[1]->connect_input(input_pointers_[2],1);
}

const std::string And3::gate_name = "And(3)";

} //namespace Virtual
