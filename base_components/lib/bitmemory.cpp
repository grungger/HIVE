#include "bitmemory.hpp"

namespace Virtual{

BitMemory::BitMemory(ptr_t save_enabler, ptr_t save_value) {
  input_pointers_[0] = save_enabler;
  input_pointers_[1] = save_value;
  circuit_components_[0] = std::make_shared<ToggledBit>(save_value, save_enabler);
  circuit_components_[1] = std::make_shared<Not>(save_enabler);
  circuit_components_[3] = std::make_shared<Delay>(circuit_components_[0]->release_output(0));
  circuit_components_[2] = std::make_shared<ToggledBit>(circuit_components_[3]->release_output(0),
						circuit_components_[1]->release_output(0));
  circuit_components_[2]->connect_output(circuit_components_[0]->release_output(0));
  output_pointers_[0] = circuit_components_[3]->release_output(0);
}


void BitMemory::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[1],0);
  circuit_components_[0]->connect_input(input_pointers_[0],1);
  circuit_components_[1]->connect_input(input_pointers_[0],0);
}

const std::string BitMemory::gate_name = "BitMemory";

void BitMemory::compute_output() {
  circuit_components_[3]->memory_release();
  for(auto it=circuit_components_.begin(); it<circuit_components_.end(); it++) {
    (*it)->compute_output();
  }
}

void BitMemory::memory_release() {
  circuit_components_[3]->memory_release();
}

} //namespace Virtual
