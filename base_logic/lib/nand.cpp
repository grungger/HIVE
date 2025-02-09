#include "nand.hpp"

namespace Virtual{

NAND::NAND(ptr_t connected1, ptr_t connected2) {
  input_pointers_[0] = connected1;
  input_pointers_[1] = connected2;
  output_pointers_[0] = std::make_shared<bool>(!((*connected1)&&(*connected2)));
}

const std::string NAND::gate_name = "NAND";

void NAND::compute_output() {
  *(output_pointers_[0]) = !((*input_pointers_[0])&&(*input_pointers_[1]));
}

}
