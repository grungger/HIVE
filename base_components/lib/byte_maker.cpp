#include "byte_maker.hpp"

namespace Virtual{

ByteMaker::ByteMaker(ptr_t in1, ptr_t in2, ptr_t in3, ptr_t in4, ptr_t in5, ptr_t in6, ptr_t in7, ptr_t in8) {
  input_pointers_[0] = in1;
  input_pointers_[1] = in2;
  input_pointers_[2] = in3;
  input_pointers_[3] = in4;
  input_pointers_[4] = in5;
  input_pointers_[5] = in6;
  input_pointers_[6] = in7;
  input_pointers_[7] = in8;
  std::uint8_t byte_value = 0;
  for (int i=0; i<8; i++) {
    byte_value |= ((*(input_pointers_[i])) << i);
  }
  byte_output_pointers_[0] = std::make_shared<byte_t>(byte_value);
}

ByteMaker::ByteMaker(ByteArg& args) {
  input_pointers_[0] = args.in1;
  input_pointers_[1] = args.in2;
  input_pointers_[2] = args.in3;
  input_pointers_[3] = args.in4;
  input_pointers_[4] = args.in5;
  input_pointers_[5] = args.in6;
  input_pointers_[6] = args.in7;
  input_pointers_[7] = args.in8;
  std::uint8_t byte_value = 0;
  for (int i=0; i<8; i++) {
    byte_value |= ((*(input_pointers_[i])) << i);
  }
  byte_output_pointers_[0] = std::make_shared<byte_t>(byte_value);
}

void ByteMaker::compute_output() {
  std::uint8_t byte_value = 0;
  for (int i=0; i<8; i++) {
    byte_value |= ((*(input_pointers_[i])) << i);
  }
  byte_t temp(byte_value);
  *(byte_output_pointers_[0]) = temp;
}

const std::string ByteMaker::gate_name = "ByteMaker";

} //namespace Virtual
