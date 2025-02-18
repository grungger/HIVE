#include "toggledbyte.hpp"

namespace Virtual{

ToggledByte::ToggledByte(ptr32_t input, ptr_t toggle) {
  input_pointers_[0] = toggle;
  byte_input_pointers_[0] = input;
  byte_output_pointers_[0] = std::make_shared<byte_t>(0);
  compute_output();
}

const std::string ToggledByte::gate_name = "ToggledByte";

void ToggledByte::compute_output() {
  if( *(input_pointers_[0]) ) {
    *(byte_output_pointers_[0]) = *(byte_input_pointers_[0]);
  }
}

void ToggledByte::connect_byte_output(ptr32_t connected_output) {
  byte_output_pointers_[0] = connected_output;
}

} //namespace Virtual
