#include "toggledbit.hpp"

namespace Virtual{

ToggledBit::ToggledBit(ptr_t conIn, ptr_t conTog) {
  input_pointers_[0] = conIn;
  input_pointers_[1] = conTog;
  circuit_components_[0] = std::make_shared<Not>(conTog);
  circuit_components_[1] = std::make_shared<And>(conIn, conTog);
  circuit_components_[2] = std::make_shared<Wire>();
  circuit_components_[3] = std::make_shared<And>(
			circuit_components_[0]->release_output(0),
			circuit_components_[2]->release_output(0));
  circuit_components_[4] = std::make_shared<Or>(
			circuit_components_[1]->release_output(0),
			circuit_components_[3]->release_output(0));
  circuit_components_[5] = std::make_shared<Wire>(
			circuit_components_[4]->release_output(0));
  circuit_components_[2]->connect_input(
			circuit_components_[5]->release_output(0), 0);

  output_pointers_[0] = circuit_components_[5]->release_output(0);
}

const std::string ToggledBit::gate_name = "ToggledBit";

void ToggledBit::connect_output(ptr_t connected_output) {
  output_pointers_[0] = connected_output;
  circuit_components_[5] = std::make_shared<Wire>(
			circuit_components_[4]->release_output(0),
			connected_output);
  circuit_components_[2]->connect_input(
			circuit_components_[5]->release_output(0),0);
}

void ToggledBit::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[1],0);
  circuit_components_[1]->connect_input(input_pointers_[0],0);
  circuit_components_[1]->connect_input(input_pointers_[1],1);
}

} //namespace Virtual
