#include "source_dest_decoder.hpp"

namespace Virtual{

SourceDestDecoder::SourceDestDecoder(ptr8_t input) {
  byte_input_pointers_[0] = input;
  circuit_components_[0] = std::make_shared<ByteSplitter>(input);
  circuit_components_[1] = std::make_shared<ThreeBitDecoder>(
				circuit_components_[0]->release_output(0),
				circuit_components_[0]->release_output(1),
				circuit_components_[0]->release_output(2));
  circuit_components_[2] = std::make_shared<ThreeBitDecoder>(
				circuit_components_[0]->release_output(3),
				circuit_components_[0]->release_output(4),
				circuit_components_[0]->release_output(5));
  circuit_components_[3] = std::make_shared<ThreeBitDecoder>();
  circuit_components_[3]->connect_input(
				circuit_components_[0]->release_output(6), 0);
  circuit_components_[3]->connect_input(
				circuit_components_[0]->release_output(7), 1);

  for (int i=0; i<8; i++) {
    output_pointers_[i] = circuit_components_[1]->release_output(i);
    output_pointers_[i+8] = circuit_components_[2]->release_output(i);
  }
  
  output_pointers_[16] = circuit_components_[3]->release_output(0);
  output_pointers_[17] = circuit_components_[3]->release_output(1);
  output_pointers_[18] = circuit_components_[3]->release_output(2);
  output_pointers_[19] = circuit_components_[3]->release_output(3);
}

void SourceDestDecoder::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
}

const std::string SourceDestDecoder::gate_name = "SourceDestDecoder";

} //namespace Virtual
