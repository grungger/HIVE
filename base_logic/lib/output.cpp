#include "output.hpp"

namespace Virtual{

int Output::counter_ = 0;

Output::Output(ptr_t connected) : id_(counter_++) { 
  input_pointers_[0] = connected;
}

const std::string Output::gate_name = "Output";

void Output::compute_output() {
  std::cout << *(input_pointers_[0]);
}

void Output::printf_out() {
  std::cout << "Output " << id_ << ":  " << *(input_pointers_[0]) << std::endl;
}



} //namespace Virtual
