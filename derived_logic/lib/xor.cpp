#include "xor.hpp"
namespace Virtual{

Xor::Xor(ptr_t connectedA, ptr_t connectedB) {
  input_pointers_[0] = connectedA;
  input_pointers_[1] = connectedB;
  circuit_components_[0] = std::make_shared<Nor>(connectedA, connectedB);
  circuit_components_[1] = std::make_shared<And>(connectedA, connectedB);
  circuit_components_[2] = std::make_shared<Nor>((circuit_components_[0]->release_output(0)),(circuit_components_[1]->release_output(0)));
  output_pointers_[0] = circuit_components_[2]->release_output(0);
}

void Xor::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[0]->connect_input(input_pointers_[1],1);
  circuit_components_[1]->connect_input(input_pointers_[0],0);
  circuit_components_[1]->connect_input(input_pointers_[1],1);
}

const std::string Xor::gate_name = "Xor";

} //namespace Virtual
