#include "xnor.hpp"
namespace Virtual{

Xnor::Xnor(ptr_t connectedA, ptr_t connectedB) {
  input_pointers_[0] = connectedA;
  input_pointers_[1] = connectedB;
  circuit_components_[0] = std::make_shared<Xor>(connectedA, connectedB);
  circuit_components_[1] = std::make_shared<Not>(circuit_components_[0]->release_output(0));
  output_pointers_[0] = circuit_components_[1]->release_output(0);
}

void Xnor::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[0]->connect_input(input_pointers_[1],1);
}

const std::string Xnor::gate_name = "Xnor";

} //namespace Virtual
