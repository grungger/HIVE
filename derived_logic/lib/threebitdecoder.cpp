#include "threebitdecoder.hpp"

namespace Virtual{

ThreeBitDecoder::ThreeBitDecoder(ptr_t in1, ptr_t in2, ptr_t in4) {
  input_pointers_[0] = in1;
  input_pointers_[1] = in2;
  input_pointers_[2] = in4;
  circuit_components_[0] = std::make_shared<OneBitDecoder>(in1);
  circuit_components_[1] = std::make_shared<OneBitDecoder>(in2);
  circuit_components_[2] = std::make_shared<OneBitDecoder>(in4);
  circuit_components_[3] = std::make_shared<And3>(
				circuit_components_[0]->release_output(0),
				circuit_components_[1]->release_output(0),
				circuit_components_[2]->release_output(0));
  circuit_components_[4] = std::make_shared<And3>(
				circuit_components_[0]->release_output(1),
				circuit_components_[1]->release_output(0),
				circuit_components_[2]->release_output(0));
  circuit_components_[5] = std::make_shared<And3>(
				circuit_components_[0]->release_output(0),
				circuit_components_[1]->release_output(1),
				circuit_components_[2]->release_output(0));
  circuit_components_[6] = std::make_shared<And3>(
				circuit_components_[0]->release_output(1),
				circuit_components_[1]->release_output(1),
				circuit_components_[2]->release_output(0));
  circuit_components_[7] = std::make_shared<And3>(
				circuit_components_[0]->release_output(0),
				circuit_components_[1]->release_output(0),
				circuit_components_[2]->release_output(1));
  circuit_components_[8] = std::make_shared<And3>(
				circuit_components_[0]->release_output(1),
				circuit_components_[1]->release_output(0),
				circuit_components_[2]->release_output(1));
  circuit_components_[9] = std::make_shared<And3>(
				circuit_components_[0]->release_output(0),
				circuit_components_[1]->release_output(1),
				circuit_components_[2]->release_output(1));
  circuit_components_[10] = std::make_shared<And3>(
				circuit_components_[0]->release_output(1),
				circuit_components_[1]->release_output(1),
				circuit_components_[2]->release_output(1));
  output_pointers_[0] = circuit_components_[3]->release_output(0);
  output_pointers_[1] = circuit_components_[4]->release_output(0);
  output_pointers_[2] = circuit_components_[5]->release_output(0);
  output_pointers_[3] = circuit_components_[6]->release_output(0);
  output_pointers_[4] = circuit_components_[7]->release_output(0);
  output_pointers_[5] = circuit_components_[8]->release_output(0);
  output_pointers_[6] = circuit_components_[9]->release_output(0);
  output_pointers_[7] = circuit_components_[10]->release_output(0);
}

void ThreeBitDecoder::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[1]->connect_input(input_pointers_[1],0);
  circuit_components_[2]->connect_input(input_pointers_[2],0);
}

const std::string ThreeBitDecoder::gate_name = "3BitDecoder";

} //namespace Virtual
