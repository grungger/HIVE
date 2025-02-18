#include "byte_not.hpp"

namespace Virtual{

ByteNot::ByteNot(ptr32_t inbyte) {
  byte_input_pointers_[0] = inbyte;
  circuit_components_[0] = std::make_shared<ByteSplitter>(inbyte);
  circuit_components_[1] = std::make_shared<Not>(circuit_components_[0]->release_output(0));
  circuit_components_[2] = std::make_shared<Not>(circuit_components_[0]->release_output(1));
  circuit_components_[3] = std::make_shared<Not>(circuit_components_[0]->release_output(2));
  circuit_components_[4] = std::make_shared<Not>(circuit_components_[0]->release_output(3));
  circuit_components_[5] = std::make_shared<Not>(circuit_components_[0]->release_output(4));
  circuit_components_[6] = std::make_shared<Not>(circuit_components_[0]->release_output(5));
  circuit_components_[7] = std::make_shared<Not>(circuit_components_[0]->release_output(6));
  circuit_components_[8] = std::make_shared<Not>(circuit_components_[0]->release_output(7));
  circuit_components_[9] = std::make_shared<ByteMaker>(
				circuit_components_[1]->release_output(0),
				circuit_components_[2]->release_output(0),
				circuit_components_[3]->release_output(0),
				circuit_components_[4]->release_output(0),
				circuit_components_[5]->release_output(0),
				circuit_components_[6]->release_output(0),
				circuit_components_[7]->release_output(0),
				circuit_components_[8]->release_output(0));
  byte_output_pointers_[0] = circuit_components_[9]->release_byte_output(0);
}

void ByteNot::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
}

const std::string ByteNot::gate_name = "ByteNot";

} //namespace Virtual

