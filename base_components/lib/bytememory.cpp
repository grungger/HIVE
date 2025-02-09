#include "bytememory.hpp"

namespace Virtual{

ByteMemory::ByteMemory(ptr_t load, ptr_t save, ptr8_t value) {
  input_pointers_[0] = load;
  input_pointers_[1] = save;
  byte_input_pointers_[0] = value;
  circuit_components_[0] = std::make_shared<ByteSplitter>(value);
  circuit_components_[1] = std::make_shared<BitMemory>(save, circuit_components_[0]->release_output(0));
  circuit_components_[2] = std::make_shared<BitMemory>(save, circuit_components_[0]->release_output(1));
  circuit_components_[3] = std::make_shared<BitMemory>(save, circuit_components_[0]->release_output(2));
  circuit_components_[4] = std::make_shared<BitMemory>(save, circuit_components_[0]->release_output(3));
  circuit_components_[5] = std::make_shared<BitMemory>(save, circuit_components_[0]->release_output(4));
  circuit_components_[6] = std::make_shared<BitMemory>(save, circuit_components_[0]->release_output(5));
  circuit_components_[7] = std::make_shared<BitMemory>(save, circuit_components_[0]->release_output(6));
  circuit_components_[8] = std::make_shared<BitMemory>(save, circuit_components_[0]->release_output(7));
  circuit_components_[9] = std::make_shared<ByteMaker>(circuit_components_[1]->release_output(0), circuit_components_[2]->release_output(0), circuit_components_[3]->release_output(0), circuit_components_[4]->release_output(0), circuit_components_[5]->release_output(0), circuit_components_[6]->release_output(0), circuit_components_[7]->release_output(0), circuit_components_[8]->release_output(0));
  circuit_components_[10] = std::make_shared<ToggledByte>(circuit_components_[9]->release_byte_output(0), load);
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
} //namespace Virtual
