#include "delay.hpp"

namespace Virtual{

Delay::Delay(ptr_t connected) {
  input_pointers_[0] = connected;
  save_ = false;
  output_pointers_[0] = std::make_shared<bool>(false);
}

const std::string Delay::gate_name = "Delay";

void Delay::compute_output() {
  *(output_pointers_[0]) = save_;
  save_ = *(input_pointers_[0]);
}

void Delay::memory_release() {
  *(output_pointers_[0]) = save_;
}

} //namespace Virtual
