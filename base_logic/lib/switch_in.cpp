#include "switch_in.hpp"

namespace Virtual{

Switch_in::Switch_in(bool set_state) : state_(set_state) {
  output_pointers_[0] = std::make_shared<bool>(state_);
}

const std::string Switch_in::gate_name = "Switch_in";

void Switch_in::compute_output() {
  *(output_pointers_[0]) = state_;
}

void Switch_in::change_state(bool new_state) {
  state_ = new_state;
  this->compute_output();
}

} //namespace Virtual
