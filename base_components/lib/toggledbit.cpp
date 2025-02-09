#include "toggledbit.hpp"

namespace Virtual{

ToggledBit::ToggledBit(ptr_t conIn, ptr_t conTog) {
  input_pointers_[0] = conIn;
  input_pointers_[1] = conTog;
  output_pointers_[0] = std::make_shared<bool>(false);
  compute_output();
}

const std::string ToggledBit::gate_name = "ToggledBit";

void ToggledBit::compute_output() {
  if ( *(input_pointers_[1]) ) {
    *(output_pointers_[0]) = *(input_pointers_[0]);
  }
}

void ToggledBit::connect_output(ptr_t connected_output) {
  output_pointers_[0] = connected_output;
  compute_output();
}

} //namespace Virtual
