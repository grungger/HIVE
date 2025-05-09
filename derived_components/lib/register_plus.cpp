#include "register_plus.hpp"

namespace Virtual{

RegisterPlus::RegisterPlus(ptr_t load, ptr_t save, ptr8_t value) {
  input_pointers_[0] = load;
  input_pointers_[1] = save;
  byte_input_pointers_[0] = value;
  circuit_components_[0] = std::make_shared<Not>();
  circuit_components_[1] = std::make_shared<ByteMemory>(
				circuit_components_[0]->release_output(0),
				save,
				value);
  circuit_components_[2] = std::make_shared<ToggledByte>(
				circuit_components_[1]->release_byte_output(0),
				load);
  byte_output_pointers_[0] = circuit_components_[2]->release_byte_output(0);
  byte_output_pointers_[1] = circuit_components_[1]->release_byte_output(0);
}

void RegisterPlus::rewire_input() {
  circuit_components_[1]->connect_input(input_pointers_[1],1);
  circuit_components_[1]->connect_byte_input(byte_input_pointers_[0],0);
  circuit_components_[2]->connect_input(input_pointers_[0], 0);
}

void RegisterPlus::memory_release() {
  circuit_components_[1]->memory_release();
  circuit_components_[2]->compute_output();
}

const std::string RegisterPlus::gate_name = "RegisterPlus";

} //namespace Virtual
