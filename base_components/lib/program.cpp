#include "program.hpp"

namespace Virtual{

Program::Program(ptr8_t locator) {
  byte_input_pointers_[0] = locator;
  byte_output_pointers_[0] = std::make_shared<byte_t>(0);
  byte_output_pointers_[1] = std::make_shared<byte_t>(0);
  byte_output_pointers_[2] = std::make_shared<byte_t>(0);
  byte_output_pointers_[3] = std::make_shared<byte_t>(0);
}

void Program::edit_code(int location, byte_t replacement) {
  code_lines[location] = replacement;
}

void Program::compute_output() {
  int index = static_cast<int>((*byte_input_pointers_[0]).value);
  (*byte_output_pointers_[0]) = code_lines[index*4+0];
  (*byte_output_pointers_[1]) = code_lines[index*4+1];
  (*byte_output_pointers_[2]) = code_lines[index*4+2];
  (*byte_output_pointers_[3]) = code_lines[index*4+3];
}

} //namespace Virtual
