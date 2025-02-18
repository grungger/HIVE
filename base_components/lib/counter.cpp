#include "counter.hpp"

namespace Virtual{

Counter::Counter(ptr_t overwrite, ptr32_t value) {
  input_pointers_[0] = overwrite;
  byte_input_pointers_[0] = value;
  circuit_components_[0] = std::make_shared<ByteMUX>(overwrite, ground32, value);
  circuit_components_[1] = std::make_shared<Not>(ground);
  circuit_components_[2] = std::make_shared<ByteMemory>(circuit_components_[1]->release_output(0), circuit_components_[1]->release_output(0), circuit_components_[0]->release_byte_output(0));
  circuit_components_[3] = std::make_shared<ByteAdder>(circuit_components_[1]->release_output(0), circuit_components_[2]->release_byte_output(0), ground32);
  circuit_components_[0]->connect_byte_input(circuit_components_[3]->release_byte_output(0),0);
  byte_output_pointers_[0] = circuit_components_[2]->release_byte_output(0);
}

void Counter::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],1);
}

void Counter::compute_output() {
  //memory release
  circuit_components_[1]->compute_output();
  circuit_components_[2]->memory_release();
  circuit_components_[3]->compute_output();
  circuit_components_[0]->compute_output();
  circuit_components_[2]->compute_output();
}

void Counter::memory_release() {
  circuit_components_[2]->memory_release();
}

const std::string Counter::gate_name = "Counter";

} //namespace Virtual
