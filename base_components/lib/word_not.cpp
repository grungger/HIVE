#include "word_not.hpp"

namespace Virtual{

ByteNot::ByteNot(ptr8_t inA, ptr8_t inB) {
  byte_input_pointers_[0] = inA;
  byte_input_pointers_[1] = inB;
  circuit_components_[0] = std::make_shared<ByteSplitter>(inA);
  circuit_components_[1] = std::make_shared<ByteSplitter>(inB);
  ByteArg argA = circuit_components_[0]->release_bytearg_output();
  ByteArg argB = circuit_components_[1]->release_bytearg_output();
  ByteArg argC;
  for (int i=0; i<8; i++) {
    circuit_components_[i+2] = std::make_shared<Not>(
				circuit_components_[0]->release_output(i),
				circuit_components_[1]->release_output(i));
    argC.bits[i] = circuit_components_[i+2]->release_output(0);
  }
  circuit_components_[10] = std::make_shared<ByteMaker>(argC);
  byte_output_pointers_[0] = circuit_components_[10]->release_byte_output(0);
}

void ByteNot::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
  circuit_components_[1]->connect_byte_input(byte_input_pointers_[1],0);
}

const std::string ByteNot::gate_name = "ByteNot";


WordNot::WordNot(ptr32_t inA, ptr32_t inB) {
  word_input_pointers_[0] = inA;
  word_input_pointers_[1] = inB;
  circuit_components_[0] = std::make_shared<WordSplitter>(inA);
  circuit_components_[1] = std::make_shared<WordSplitter>(inB);
  WordArg argA = circuit_components_[0]->release_wordarg_output();
  WordArg argB = circuit_components_[1]->release_wordarg_output();
  WordArg argC;
  for (int i=0; i<32; i++) {
    circuit_components_[i+2] = std::make_shared<Not>(
				circuit_components_[0]->release_output(i),
				circuit_components_[1]->release_output(i));
    argC.bits[i] = circuit_components_[i+2]->release_output(0);
  }
  circuit_components_[34] = std::make_shared<WordMaker>(argC);
  word_output_pointers_[0] = circuit_components_[34]->release_word_output(0);
}

void WordNot::rewire_input() {
  circuit_components_[0]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[1]->connect_word_input(word_input_pointers_[1],0);
}

const std::string WordNot::gate_name = "WordNot";


} //namespace Virtual
