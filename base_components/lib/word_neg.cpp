#include "word_neg.hpp"

namespace Virtual{

ByteNeg::ByteNeg(ptr8_t in) {
  byte_input_pointers_[0] = in;
  circuit_components_[0] = std::make_shared<ByteNot>(in);
  circuit_components_[1] = std::make_shared<Not>(ground);
  circuit_components_[2] = std::make_shared<ByteAdder>(
				circuit_components_[1]->release_output(0),
				cicruict_components_[0]->release_byte_output(0),
				ground8 );
  byte_output_pointers_[0] = circuit_components_[2]->release_byte_output(0);
}

void ByteNeg::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
}

const std::string ByteNeg::gate_name = "ByteNeg";


WordNeg::WordNeg(ptr32_t in) {
  word_input_pointers_[0] = in;
  circuit_components_[0] = std::make_shared<WordNot>(in);
  circuit_components_[1] = std::make_shared<Not>(ground);
  circuit_components_[2] = std::make_shared<WordAdder>(
				circuit_components_[1]->release_output(0),
				circuit_components_[0]->release_word_output(0),
				ground32 );
  word_output_pointers_[0] = circuit_components_[2]->release_word_output(0);
}

void WordNeg::rewire_input() {
  circuit_components_[0]->connect_word_input(word_input_pointers_[0],0);
}

const std::string WordNeg::gate_name = "WordNeg";


} //namespace Virtual
