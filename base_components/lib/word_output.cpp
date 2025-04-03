#include "word_output.hpp"
#include <iostream>

namespace Virtual{

int ByteOutput::counter_ = 0;
int WordOutput::counter_ = 0;

ByteOutput::ByteOutput(ptr8_t connector) : id_(counter_++) {
  byte_input_pointers_[0] = connector;
}

const std::string ByteOutput::gate_name = "ByteOutput";

void ByteOutput::compute_output() {
  std::cout << *(byte_input_pointers_[0]);
}

void ByteOutput::printf_out() {
  std::cout << "ByteOutput " << id_ << ": " << *(byte_input_pointers_[0]) << std::endl;
}

WordOutput::WordOutput(ptr32_t connector) : id_(counter_++) {
  word_input_pointers_[0] = connector;
}

const std::string WordOutput::gate_name = "WordOutput";

void WordOutput::compute_output() {
  std::cout << *(word_input_pointers_[0]);
}

void WordOutput::printf_out() {
  std::cout << "WordOutput " << id_ << ": " << *(word_input_pointers_[0]) << std::endl;
}

} //namespace Virtual
