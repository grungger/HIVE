#include "onebitdecoder.hpp"

namespace Virtual{

OneBitDecoder::OneBitDecoder(ptr_t input) {
  input_pointers_[0] = input;
  circuit_components_[0] = std::make_shared<Not>(input);
  circuit_components_[1] = std::make_shared<Wire>(input);
  output_pointers_[0] = circuit_components_[0]->release_output(0);
  output_pointers_[1] = circuit_components_[1]->release_output(0);
}

void OneBitDecoder::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[1]->connect_input(input_pointers_[0],0);
}

const std::string OneBitDecoder::gate_name = "1BitDecoder";

} //namespace Virtual
