#include "byteswitch_in.hpp"

namespace Virtual{

ByteSwitch_in::ByteSwitch_in(byte_t InByte) : state_(InByte) {
  byte_output_pointers_[0] = std::make_shared<byte_t>(InByte);
}

ByteSwitch_in::ByteSwitch_in(std::uint8_t num) : state_(num) {
  byte_output_pointers_[0] = std::make_shared<byte_t>(state_);
}

const std::string ByteSwitch_in::gate_name = "ByteSwitch_in";

void ByteSwitch_in::compute_output() {
   *(byte_output_pointers_[0]) = state_;
}

void ByteSwitch_in::change_state(byte_t InByte) {
  this->state_ = InByte;
  this->compute_output();
}

void ByteSwitch_in::change_state(std::uint8_t num) {
  byte_t temp(num);
  this->state_ = temp;
  this->compute_output();
}

} //namespace Virtual
