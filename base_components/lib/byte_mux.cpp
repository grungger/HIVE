#include "byte_mux.hpp"

namespace Virtual{

ByteMUX::ByteMUX(ptr_t toggler, ptr8_t  inA, ptr8_t inB) {
  input_pointers_[0] = toggler;
  byte_input_pointers_[0] = inA;
  byte_input_pointers_[1] = inB;
  circuit_components_[0] = std::make_shared<Not>(toggler);
  circuit_components_[1] = std::make_shared<ToggledByte>(inA,circuit_components_[0]->release_output(0));
  circuit_components_[2] = std::make_shared<ToggledByte>(inB,toggler);
  byte_output_pointers_[0] = circuit_components_[2]->release_byte_output(0);
  circuit_components_[1]->connect_byte_output(circuit_components_[2]->release_byte_output(0));
}

void ByteMUX::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[1]->connect_byte_input(byte_input_pointers_[0],0);
  circuit_components_[2]->connect_byte_input(byte_input_pointers_[1],0);
  circuit_components_[2]->connect_input(input_pointers_[0],0);
}

const std::string gate_name = "ByteMUX";

} //namespace Virtual
