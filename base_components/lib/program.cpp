#include "program.hpp"

namespace Virtual{

ByteProgram::ByteProgram(ptr8_t locator) {
  byte_input_pointers_[0] = locator;
  byte_output_pointers_[0] = std::make_shared<byte_t>(0);
}

void ByteProgram::edit_code(int location, byte_t replacement) {
  if (static_cast<size_t>(location) >= code_lines.size()) {
    throw std::domain_error("Location out of range");
  }
  code_lines[location] = replacement;
}

void ByteProgram::compute_output() {
  int index = static_cast<int>((*byte_input_pointers_[0]).value);
  if (static_cast<size_t>(index) >= code_lines.size()) {
    throw std::domain_error("Counter value is out of range of program");
  }
  (*byte_output_pointers_[0]) = code_lines[index];
}


Program::Program(ptr32_t locator) {
  word_input_pointers_[0] = locator;
  byte_word_bool = true;
  word_output_pointers_[0] = std::make_shared<word_t>(0);
}

void Program::edit_code(int location, word_t replacement) {
  if (static_cast<size_t>(location) >= code_lines.size()) {
    throw std::domain_error("Location out of range");
  }
  code_lines[location] = replacement;
}

void Program::compute_output() {
  int index;
  if (byte_word_bool) {
    index = static_cast<int>((*word_input_pointers_[0]).value);
  }
  else {
    index = static_cast<int>((*byte_input_pointers_[0]).value);
  }
  if (static_cast<size_t>(index) >= code_lines.size()) {
    throw std::domain_error("Counter value " + std::to_string(index) + " is out of range of program");
  }
  (*word_output_pointers_[0]) = code_lines[index];
}

} //namespace Virtual
