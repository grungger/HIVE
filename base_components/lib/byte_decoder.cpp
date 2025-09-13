#include "byte_decoder.hpp"

namespace Virtual {

ByteDecoder::ByteDecoder(ptr8_t conA) {
  byte_input_pointers_[0] = conA;
  int avoid = static_cast<int>((conA)->value);

  for (int i=0; i<256; i++) {
    if (i == avoid) {
      output_pointers_[avoid] = std::make_shared<bool>(true);
      continue;
    }
    output_pointers_[i] = std::make_shared<bool>(false);
  }
}

void ByteDecoder::compute_output() {
  int avoid = static_cast<int>((byte_input_pointers_[0])->value);

  for (int i=0; i<256; i++) {
    if (i == avoid) {
      *(output_pointers_[avoid]) = true;
      continue;
    }
    *(output_pointers_[i]) = false;
  }
}

const std::string ByteDecoder::gate_name = "ByteDecoder";

} //namespace Virtual
