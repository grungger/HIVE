#include "byte_neg.hpp"

namespace Virtual{

ByteNeg::ByteNeg(ptr8_t input) {
  byte_input_pointers_[0] = input;
  circuit_components_[0] = std::make_shared<ByteNot>(input);
  circuit_components_[1] = std::make_shared<Not>(ground);
  circuit_components_[2] = std::make_shared<ByteAdder>(circuit_components_[1]->release_output(0), circuit_components_[0]->release_byte_output(0), ground8);
  byte_output_pointers_[0] = circuit_components_[2]->release_byte_output(0);
}

void ByteNeg::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
}

const std::string ByteNeg::gate_name = "ByteNeg";

} //namespace Virtual
