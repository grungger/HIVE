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

void RegisterPlus::connect_byte_output(ptr8_t conOut) {
  byte_output_pointers_[0] = conOut;
  circuit_components_[2]->connect_byte_output(conOut);
}

const std::string RegisterPlus::gate_name = "RegisterPlus";


RegisterMax::RegisterMax(ptr_t load, ptr_t save, ptr32_t value) {
  input_pointers_[0] = load;
  input_pointers_[1] = save;
  word_input_pointers_[0] = value;
  circuit_components_[0] = std::make_shared<Not>();
  circuit_components_[1] = std::make_shared<WordMemory>(
				circuit_components_[0]->release_output(0),
				save,
				value);
  circuit_components_[2] = std::make_shared<ToggledWord>(
				circuit_components_[1]->release_word_output(0),
				load);
  word_output_pointers_[0] = circuit_components_[2]->release_word_output(0);
  word_output_pointers_[1] = circuit_components_[1]->release_word_output(0);
}

void RegisterMax::rewire_input() {
  circuit_components_[1]->connect_input(input_pointers_[1],1);
  circuit_components_[1]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[2]->connect_input(input_pointers_[0], 0);
}

void RegisterMax::memory_release() {
  circuit_components_[1]->memory_release();
  circuit_components_[2]->compute_output();
}

void RegisterMax::connect_word_output(ptr32_t conOut) {
  word_output_pointers_[0] = conOut;
  circuit_components_[2]->connect_word_output(conOut);
}

const std::string RegisterMax::gate_name = "RegisterMax";

} //namespace Virtual
