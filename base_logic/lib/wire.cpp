#include "wire.hpp"

namespace Virtual{

Wire::Wire(ptr_t input) {
  input_pointers_[0] = input;
  output_pointers_[0] = std::make_shared<bool>(*input);
}

const std::string Wire::gate_name = " ";

void Wire::compute_output() {
  *(output_pointers_[0]) = *(input_pointers_[0]);
}

} //namespace Virtual
