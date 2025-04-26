#include "toggledword.hpp"

namespace Virtual{

ToggledByte::ToggledByte(ptr8_t input, ptr_t toggle) {
  input_pointers_[0] = toggle;
  byte_input_pointers_[0] = input;
  circuit_components_[0] = std::make_shared<ByteSplitter>(input);
  circuit_components_[1] = std::make_shared<Not>(toggle);
  circuit_components_[35] = std::make_shared<ByteMaker>();
  circuit_components_[36] = std::make_shared<ByteWire>(
				circuit_components_[35]->release_byte_output(0));
  circuit_components_[2] = std::make_shared<ByteSplitter>(
				circuit_components_[36]->release_byte_output(0));
  int x = 4;
  int offset = 3;
  for (int i=0; i<8; i++) {
    circuit_components_[x*i+offset] = std::make_shared<And>(
				circuit_components_[0]->release_output(i), toggle);
    circuit_components_[x*i+offset+1] = std::make_shared<And>(
				circuit_components_[1]->release_output(0),
				circuit_components_[2]->release_output(i));
    circuit_components_[x*i+offset+2] = std::make_shared<Or>(
				circuit_components_[x*i+offset]->release_output(0),
				circuit_components_[x*i+offset+1]->release_output(0));
    circuit_components_[x*i+offset+3] = std::make_shared<Wire>(
				circuit_components_[x*i+offset+2]->release_output(0));
    circuit_components_[35]->connect_input(
    				circuit_components_[x*i+offset+3]->release_output(0), i);


  }
  byte_output_pointers_[0] = circuit_components_[36]->release_byte_output(0);
  // TODO: test whether it requires compute_output() here, to have identical behavior
  //   as ToggledBit on instantiation.
}

const std::string ToggledByte::gate_name = "ToggledByte";

void ToggledByte::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0], 0);
  circuit_components_[1]->connect_input(input_pointers_[0], 0);
  for (int i=0; i<8; i++) {
    circuit_components_[4*i+3]->connect_input(input_pointers_[0], 1);
  }
}

void ToggledByte::connect_byte_output(ptr8_t connected_output) {
  byte_output_pointers_[0] = connected_output;
  circuit_components_[36] = std::make_shared<ByteWire>(
				circuit_components_[35]->release_byte_output(0),
				connected_output);
  circuit_components_[2]->connect_byte_input(connected_output,0);
}


ToggledWord::ToggledWord(ptr32_t input, ptr_t toggle) {
  input_pointers_[0] = toggle;
  word_input_pointers_[0] = input;
  circuit_components_[0] = std::make_shared<WordSplitter>(input);
  circuit_components_[1] = std::make_shared<Not>(toggle);
  circuit_components_[131] = std::make_shared<WordMaker>();
  circuit_components_[132] = std::make_shared<WordWire>(
			circuit_components_[131]->release_word_output(0));
  circuit_components_[2] = std::make_shared<WordSplitter>(
			circuit_components_[132]->release_word_output(0));
  int x = 4;
  int offset = 3;
  for (int i=0; i<32; i++) {
    circuit_components_[x*i+offset] = std::make_shared<And>(
				circuit_components_[0]->release_output(i), toggle);
    circuit_components_[x*i+offset+1] = std::make_shared<And>(
				circuit_components_[1]->release_output(0),
				circuit_components_[2]->release_output(i));
    circuit_components_[x*i+offset+2] = std::make_shared<Or>(
				circuit_components_[x*i+offset]->release_output(0),
				circuit_components_[x*i+offset+1]->release_output(0));
    circuit_components_[x*i+offset+3] = std::make_shared<Wire>(
				circuit_components_[x*i+offset+2]->release_output(0));
    circuit_components_[131]->connect_input(
				circuit_components_[x*i+offset+3]->release_output(0),
				i );
  }
  word_output_pointers_[0] = circuit_components_[132]->release_word_output(0);
}

const std::string ToggledWord::gate_name = "ToggledWord";

void ToggledWord::rewire_input() {
  circuit_components_[0]->connect_word_input(word_input_pointers_[0], 0);
  circuit_components_[1]->connect_input(input_pointers_[0], 0);
  for (int i=0; i<32; i++) {
    circuit_components_[4*i+3]->connect_input(input_pointers_[0], 1);
  }
}

void ToggledWord::connect_word_output(ptr32_t connected_output) {
  word_output_pointers_[0] = connected_output;
  circuit_components_[132] = std::make_shared<WordWire>(
				circuit_components_[131]->release_word_output(0),
				connected_output);
  circuit_components_[2]->connect_word_input(connected_output, 0);
}

} //namespace Virtual
