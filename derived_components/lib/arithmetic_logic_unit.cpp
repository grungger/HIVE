#include "arithmetic_logic_unit.hpp"

namespace Virtual{

ArithmeticLogicUnit::ArithmeticLogicUnit(ptr8_t instruction, 
					ptr8_t inputA, ptr8_t inputB) {
  byte_input_pointers_[0] = instruction;
  byte_input_pointers_[1] = inputA;
  byte_input_pointers_[2] = inputB;
  circuit_components_[0] = std::make_shared<ByteSplitter>(instruction);
  circuit_components_[1] = std::make_shared<ThreeBitDecoder>(
				circuit_components_[0]->release_output(0),
				circuit_components_[0]->release_output(1),
				circuit_components_[0]->release_output(2));
  circuit_components_[2] = std::make_shared<ByteOr>(inputA,inputB);
  circuit_components_[3] = std::make_shared<ByteNot>(inputA);
  circuit_components_[4] = std::make_shared<ByteNot>(inputB);
  circuit_components_[5] = std::make_shared<ByteOr>(
		  		circuit_components_[3]->release_byte_output(0),
				circuit_components_[4]->release_byte_output(0));
  circuit_components_[6] = std::make_shared<ToggledByte>(
		  		circuit_components_[2]->release_byte_output(0),
				circuit_components_[1]->release_output(0));
  circuit_components_[7] = std::make_shared<ByteNot>(
				circuit_components_[2]->release_byte_output(0));
  circuit_components_[8] = std::make_shared<ToggledByte>(
		  		circuit_components_[7]->release_byte_output(0),
				circuit_components_[1]->release_output(2));
  circuit_components_[8]->connect_byte_output(
		 	circuit_components_[6]->release_byte_output(0));
  circuit_components_[9] = std::make_shared<ToggledByte>(
		  	circuit_components_[5]->release_byte_output(0),
			circuit_components_[1]->release_output(1));
  circuit_components_[9]->connect_byte_output(
		  	circuit_components_[6]->release_byte_output(0));
  circuit_components_[10] = std::make_shared<ByteNot>(
		  		circuit_components_[5]->release_byte_output(0));
  circuit_components_[11] = std::make_shared<ToggledByte>(
		  		circuit_components_[10]->release_byte_output(0),
				circuit_components_[1]->release_output(3));
  circuit_components_[11]->connect_byte_output(
		 	circuit_components_[6]->release_byte_output(0)); 
  circuit_components_[12] = std::make_shared<ByteAdder>();
  circuit_components_[12]->connect_byte_input(inputA,0);
  circuit_components_[12]->connect_byte_input(inputB,1);
  circuit_components_[13] = std::make_shared<ToggledByte>(
		  		circuit_components_[12]->release_byte_output(0),
				circuit_components_[1]->release_output(4));
  circuit_components_[13]->connect_byte_output(
		  	circuit_components_[6]->release_byte_output(0));
  circuit_components_[14] = std::make_shared<ByteNeg>(inputB);
  circuit_components_[15] = std::make_shared<ByteAdder>();
  circuit_components_[15]->connect_byte_input(inputA, 0);
  circuit_components_[15]->connect_byte_input(
		  		circuit_components_[14]->release_byte_output(0),1);
  circuit_components_[16] = std::make_shared<ToggledByte>(
		  		circuit_components_[15]->release_byte_output(0),
				circuit_components_[1]->release_output(5));
  circuit_components_[16]->connect_byte_output(
		  	circuit_components_[6]->release_byte_output(0));
  
  byte_output_pointers_[0] = circuit_components_[6]->release_byte_output(0);
}

void ArithmeticLogicUnit::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
  circuit_components_[2]->connect_byte_input(byte_input_pointers_[1],0);
  circuit_components_[2]->connect_byte_input(byte_input_pointers_[2],1);
  circuit_components_[3]->connect_byte_input(byte_input_pointers_[1],0);
  circuit_components_[4]->connect_byte_input(byte_input_pointers_[2],0);
  circuit_components_[12]->connect_byte_input(byte_input_pointers_[1],0);
  circuit_components_[12]->connect_byte_input(byte_input_pointers_[2],1);
  circuit_components_[14]->connect_byte_input(byte_input_pointers_[2],0);
  circuit_components_[15]->connect_byte_input(byte_input_pointers_[1],0);
}

const std::string ArithmeticLogicUnit::gate_name = "ArithmeticLogicUnit";

} //namespace Virtual
