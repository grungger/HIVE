#include "word_not.hpp"

namespace Virtual{

ByteNot::ByteNot(ptr8_t in) {
  byte_input_pointers_[0] = in;
  circuit_components_[0] = std::make_shared<ByteSplitter>(in);
  ByteArg Arg = circuit_components_[0]->release_bytearg_output();
  ByteArg argC;
  for (int i=0; i<8; i++) {
    circuit_components_[i+1] = std::make_shared<Not>(
				circuit_components_[0]->release_output(i) );
    argC.bits[i] = circuit_components_[i+1]->release_output(0);
  }
  circuit_components_[9] = std::make_shared<ByteMaker>(argC);
  byte_output_pointers_[0] = circuit_components_[9]->release_byte_output(0);
}

void ByteNot::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
}

const std::string ByteNot::gate_name = "ByteNot";


WordNot::WordNot(ptr32_t in) {
  word_input_pointers_[0] = in;
  circuit_components_[0] = std::make_shared<WordSplitter>(in);
  WordArg Arg = circuit_components_[0]->release_wordarg_output();
  WordArg argC;
  for (int i=0; i<32; i++) {
    circuit_components_[i+1] = std::make_shared<Not>(
				circuit_components_[0]->release_output(i) );
    argC.bits[i] = circuit_components_[i+1]->release_output(0);
  }
  circuit_components_[33] = std::make_shared<WordMaker>(argC);
  word_output_pointers_[0] = circuit_components_[33]->release_word_output(0);
}

void WordNot::rewire_input() {
  circuit_components_[0]->connect_word_input(word_input_pointers_[0],0);
}

const std::string WordNot::gate_name = "WordNot";


} //namespace Virtual
