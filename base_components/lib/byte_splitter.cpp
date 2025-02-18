#include "byte_splitter.hpp"

namespace Virtual {

ByteSplitter::ByteSplitter(ptr32_t conA) {
  byte_input_pointers_[0] = conA;
  for (int i=0; i<8; i++) {
    output_pointers_[i] = std::make_shared<bool>((*conA)[i]);
  }
}

const std::string ByteSplitter::gate_name = "ByteSplitter";

void ByteSplitter::compute_output() {
  for (int i=0; i<8; i++) {
    *(output_pointers_[i]) = (*byte_input_pointers_[0])[i];
  }
}

} //namespace Virtual
