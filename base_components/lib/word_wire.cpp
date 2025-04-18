#include "word_wire.hpp"

namespace Virtual{

ByteWire::ByteWire(ptr8_t input) {
  byte_input_pointers_[0] = input;
  byte_output_pointers_[0] = std::make_shared<byte_t>(*input);
}

ByteWire::ByteWire(ptr8_t input, ptr8_t output) {
  byte_input_pointers_[0] = input;
  byte_output_pointers_[0] = output;
}

const std::string ByteWire::gate_name = "ByteWire";

void ByteWire::compute_output() {
  byte_output_pointers_[0]->value = byte_input_pointers_[0]->value;
}


WordWire::WordWire(ptr32_t input) {
  word_input_pointers_[0] = input;
  word_output_pointers_[0] = std::make_shared<word_t>(*input);
}

WordWire::WordWire(ptr32_t input, ptr32_t output) {
  word_input_pointers_[0] = input;
  word_output_pointers_[0] = output;
}

const std::string WordWire::gate_name = "WordWire";

void WordWire::compute_output() {
  word_output_pointers_[0]->value = word_input_pointers_[0]->value;
}

} //namespace Virtual
