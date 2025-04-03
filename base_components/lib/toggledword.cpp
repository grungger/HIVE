#include "toggledword.hpp"

namespace Virtual{

ToggledByte::ToggledByte(ptr8_t input, ptr_t toggle) {
  input_pointers_[0] = toggle;
  byte_input_pointers_[0] = input;
  circuit_components_[0] = std::make_shared<ByteSplitter>(input);
  circuit_components_[9] = std::make_shared<ByteMaker>();
  for (int i=0; i<8; i++) {
    circuit_components_[i+1] = std::make_shared<ToggledBit>(
				circuit_components_[0]->release_output(i), toggle);
    circuit_components_[9]->connect_input(
				circuit_components_[i+1]->release_output(0), i);
  }
  circuit_components_[10] = std::make_shared<ByteWire>(
				circuit_components_[9]->release_byte_output(0));
  byte_output_pointers_[0] = circuit_components_[10]->release_byte_output(0);
  // TODO: test whether it requires compute_output() here, to have identical behavior
  //   as ToggledBit on instantiation.
}

const std::string ToggledByte::gate_name = "ToggledByte";

void ToggledByte::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0], 0);
}

void ToggledByte::connect_byte_output(ptr8_t connected_output) {
  byte_output_pointers_[0] = connected_output;
  circuit_components_[10] = std::make_shared<ByteWire>(
				circuit_components_[9]->release_byte_output(0),
				connected_output);
}


ToggledWord::ToggledWord(ptr32_t input, ptr_t toggle) {
  input_pointers_[0] = toggle;
  word_input_pointers_[0] = input;
  circuit_components_[0] = std::make_shared<WordSplitter>(input);
  circuit_components_[33] = std::make_shared<WordMaker>();
  for (int i=0; i<32; i++) {
    circuit_components_[i+1] = std::make_shared<ToggledBit>(
				circuit_components_[0]->release_output(i), toggle);
    circuit_components_[33]->connect_input(
				circuit_components_[i+1]->release_output(0), i);
  }
  circuit_components_[34] = std::make_shared<WordWire>(
				circuit_components_[33]->release_word_output(0));
  word_output_pointers_[0] = circuit_components_[34]->release_word_output(0);
  // TODO: test whether we need compute_output()
}

const std::string ToggledWord::gate_name = "ToggledWord";

void ToggledWord::rewire_input() {
  circuit_components_[0]->connect_word_input(word_input_pointers_[0], 0);
}

void ToggledWord::connect_word_output(ptr32_t connected_output) {
  word_output_pointers_[0] = connected_output;
  circuit_components_[34] = std::make_shared<WordWire>(
				circuit_components_[33]->release_word_output(0),
				connected_output);
}

} //namespace Virtual
