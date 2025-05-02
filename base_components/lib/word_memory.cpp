#include "word_memory.hpp"

namespace Virtual{

ByteMemory::ByteMemory(ptr_t load, ptr_t save, ptr8_t value) {
  input_pointers_[0] = load;
  input_pointers_[1] = save;
  byte_input_pointers_[0] = value;
  circuit_components_[0] = std::make_shared<ByteSplitter>(value);
  ByteArg arg;
  for (int i=0; i<8; i++) {
    circuit_components_[i+1] = std::make_shared<BitMemory>(save,
				circuit_components_[0]->release_output(i));
    arg.bits[i] = circuit_components_[i+1]->release_output(0);
  }
  circuit_components_[9] = std::make_shared<ByteMaker>(arg);
  circuit_components_[10] = std::make_shared<ToggledByte>(
				circuit_components_[9]->release_byte_output(0),
				load );
  circuit_components_[10]->init();
  byte_output_pointers_[0] = circuit_components_[10]->release_byte_output(0);
}

void ByteMemory::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
  circuit_components_[1]->connect_input(input_pointers_[1],0);
  circuit_components_[2]->connect_input(input_pointers_[1],0);
  circuit_components_[3]->connect_input(input_pointers_[1],0);
  circuit_components_[4]->connect_input(input_pointers_[1],0);
  circuit_components_[5]->connect_input(input_pointers_[1],0);
  circuit_components_[6]->connect_input(input_pointers_[1],0);
  circuit_components_[7]->connect_input(input_pointers_[1],0);
  circuit_components_[8]->connect_input(input_pointers_[1],0);
  circuit_components_[10]->connect_input(input_pointers_[0],0);
}

void ByteMemory::memory_release() {
  if (*input_pointers_[0]) {
    for(int i=1; i<9; i++) {
      circuit_components_[i]->memory_release();
    }
    circuit_components_[9]->compute_output();
    circuit_components_[10]->compute_output();
  }
}

const std::string ByteMemory::gate_name = "ByteMemory";

// WordMemory
WordMemory::WordMemory(ptr_t load, ptr_t save, ptr32_t value) {
  input_pointers_[0] = load;
  input_pointers_[1] = save;
  word_input_pointers_[0] = value;
  circuit_components_[0] = std::make_shared<WordSplitter>(value);
  WordArg arg;
  for (int i=0; i<32; i++) {
    circuit_components_[i+1] = std::make_shared<BitMemory>(save,
				circuit_components_[0]->release_output(i));
    arg.bits[i] = circuit_components_[i+1]->release_output(0);
  }
  circuit_components_[33] = std::make_shared<WordMaker>(arg);
  circuit_components_[34] = std::make_shared<ToggledWord>(
				circuit_components_[33]->release_word_output(0),
				load );
  circuit_components_[34]->init();
  word_output_pointers_[0] = circuit_components_[34]->release_word_output(0);
}

void WordMemory::rewire_input() {
  circuit_components_[0]->connect_word_input(word_input_pointers_[0],0);
  for (int i=0; i<32; i++) {
    circuit_components_[i+1]->connect_input(input_pointers_[1],0);
  }
  circuit_components_[34]->connect_input(input_pointers_[0],0);
}

void WordMemory::memory_release() {
  if (*input_pointers_[0]) {
    for(int i=0; i<32; i++) {
      circuit_components_[i+1]->memory_release();
    }
    circuit_components_[33]->compute_output();
    circuit_components_[34]->compute_output();
  }
}

const std::string WordMemory::gate_name = "WordMemory";

} //namespace Virtual
