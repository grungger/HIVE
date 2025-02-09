#include "nor.hpp"
namespace Virtual{

Nor::Nor(ptr_t connectedA, ptr_t connectedB) {
  input_pointers_[0] = connectedA;
  input_pointers_[1] = connectedB;
  circuit_components_[0] = std::make_shared<Not>(connectedA);
  circuit_components_[1] = std::make_shared<Not>(connectedB);
  circuit_components_[2] = std::make_shared<NAND>((circuit_components_[0]->release_output(0)), (circuit_components_[1]->release_output(0)));
  circuit_components_[3] = std::make_shared<Not>(circuit_components_[2]->release_output(0));
  output_pointers_[0] = circuit_components_[3]->release_output(0);
}

void Nor::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[1]->connect_input(input_pointers_[1],0);
}

const std::string Nor::gate_name = "NOr";

} //namespace Virtual  
