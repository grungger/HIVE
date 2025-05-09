#include "conditional_unit.hpp"

namespace Virtual{

ConditionalUnit::ConditionalUnit(ptr8_t condition, ptr8_t input) {
  byte_input_pointers_[0] = condition;
  byte_input_pointers_[1] = input;
  circuit_components_[0] = std::make_shared<ByteSplitter>(condition);
  circuit_components_[1] = std::make_shared<ThreeBitDecoder>(
				circuit_components_[0]->release_output(0),
				circuit_components_[0]->release_output(1),
				circuit_components_[0]->release_output(2));
  circuit_components_[2] = std::make_shared<Not>();
  circuit_components_[3] = std::make_shared<ByteNot>(input);
  circuit_components_[4] = std::make_shared<ByteAdder>();
  circuit_components_[4]->connect_input(
			circuit_components_[2]->release_output(0), 0);
  circuit_components_[4]->connect_byte_input(
			circuit_components_[3]->release_byte_output(0), 1);
  circuit_components_[5] = std::make_shared<ByteSplitter>(input);
  circuit_components_[6] = std::make_shared<ToggledBit>();
  circuit_components_[6]->connect_input(
		  	circuit_components_[1]->release_output(0), 1);
  circuit_components_[7] = std::make_shared<ToggledBit>(
		  		circuit_components_[4]->release_output(0),
				circuit_components_[1]->release_output(1));
  circuit_components_[7]->connect_output(
		  	circuit_components_[6]->release_output(0));
  circuit_components_[8] = std::make_shared<ToggledBit>(
		  		circuit_components_[5]->release_output(7),
				circuit_components_[1]->release_output(2));
  circuit_components_[8]->connect_output(
		 	circuit_components_[6]->release_output(0));
  circuit_components_[9] = std::make_shared<Or>(
		  	circuit_components_[4]->release_output(0),
			circuit_components_[5]->release_output(7));
  circuit_components_[10] = std::make_shared<ToggledBit>(
		  		circuit_components_[9]->release_output(0),
				circuit_components_[1]->release_output(3));
  circuit_components_[10]->connect_output(
		  	circuit_components_[6]->release_output(0));
  circuit_components_[11] = std::make_shared<ToggledBit>(
		  		circuit_components_[2]->release_output(0),
				circuit_components_[1]->release_output(4));
  circuit_components_[11]->connect_output(
		 	circuit_components_[6]->release_output(0)); 
  circuit_components_[12] = std::make_shared<Not>(
		  		circuit_components_[4]->release_output(0));
  circuit_components_[13] = std::make_shared<ToggledBit>(
		  		circuit_components_[12]->release_output(0),
				circuit_components_[1]->release_output(5));
  circuit_components_[13]->connect_output(
		  	circuit_components_[6]->release_output(0));
  circuit_components_[14] = std::make_shared<Not>(
		  		circuit_components_[5]->release_output(7));
  circuit_components_[15] = std::make_shared<ToggledBit>(
		  		circuit_components_[14]->release_output(0),
				circuit_components_[1]->release_output(6));
  circuit_components_[15]->connect_output(
		 	circuit_components_[6]->release_output(0)); 
  circuit_components_[16] = std::make_shared<Not>(
		  		circuit_components_[9]->release_output(0));
  circuit_components_[17] = std::make_shared<ToggledBit>(
		  		circuit_components_[16]->release_output(0),
				circuit_components_[1]->release_output(7));
  circuit_components_[17]->connect_output(
		  	circuit_components_[6]->release_output(0));
  
  output_pointers_[0] = circuit_components_[6]->release_output(0);
}

void ConditionalUnit::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
  circuit_components_[5]->connect_byte_input(byte_input_pointers_[1],0);
}

const std::string ConditionalUnit::gate_name = "ConditionalUnit";

} //namespace Virtual
