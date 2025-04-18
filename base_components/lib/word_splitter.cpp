#include "word_splitter.hpp"

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

} //namespace Virtual
