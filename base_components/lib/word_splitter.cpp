#include "word_splitter.hpp"
#include <cmath>

namespace Virtual {

ByteSplitter::ByteSplitter(ptr8_t conA) {
  byte_input_pointers_[0] = conA;
  for (int i=0; i<8; i++) {
    output_pointers_[i] = std::make_shared<bool>((*conA)[i]);
  }
}

void ByteSplitter::compute_output() {
  for (int i=0; i<8; i++) {
    *(output_pointers_[i]) = (*byte_input_pointers_[0])[i];
  }
}

ByteArg ByteSplitter::release_bytearg_output() {
  ByteArg output;
  for (int i=0; i<8; i++) {
    output.bits[i] = this->release_output(i);
  }
  return output;
}

const std::string ByteSplitter::gate_name = "ByteSplitter";


WordSplitter::WordSplitter(ptr32_t conA) {
  word_input_pointers_[0] = conA;
  for (int i=0; i<32; i++) {
    output_pointers_[i] = std::make_shared<bool>((*conA)[i]);
  }
}

const std::string WordSplitter::gate_name = "WordSplitter";

void WordSplitter::compute_output() {
  for (int i=0; i<32; i++) {
    *(output_pointers_[i]) = (*word_input_pointers_[0])[i];
  }
}

WordArg WordSplitter::release_wordarg_output() {
  WordArg output;
  for (int i=0; i<32; i++) {
    output.bits[i] = this->release_output(i);
  }
  return output;
}

WordByter::WordByter(ptr32_t conA) {
  word_input_pointers_[0] = conA;
  for (int i=0; i<4; i++) {
    std::uint8_t ithByte = 0;
    for (int j=0; j<8; j++) {
      ithByte += (*conA)[8*i+j] * std::pow(2,j);
    }
    byte_output_pointers_[i] = std::make_shared<byte_t>(ithByte);
  }
}

const std::string WordByter::gate_name = "WordByter";

void WordByter::compute_output() {
  for (int i=0; i<4; i++) {
    std::uint8_t ithByte = 0;
    for (int j=0; j<8; j++) {
      ithByte += (*word_input_pointers_[0])[8*i+j] * std::pow(2,j);
    }
    *(byte_output_pointers_[i]) = ithByte;
  }
}


ByteSF::ByteSF(ptr8_t conA) {
  byte_input_pointers_[0] = conA;
  output_pointers_[0] = std::make_shared<bool>((*conA)[7]);
}

const std::string ByteSF::gate_name = "ByteSF";

void ByteSF::compute_output() {
  *(output_pointers_[0]) = (*byte_input_pointers_[0])[7];
}


WordSF::WordSF(ptr32_t conA) {
  word_input_pointers_[0] = conA;
  output_pointers_[0] = std::make_shared<bool>((*conA)[31]);
}

const std::string WordSF::gate_name = "WordSF";

void WordSF::compute_output() {
  *(output_pointers_[0]) = (*word_input_pointers_[0])[31];
}


} //namespace Virtual
