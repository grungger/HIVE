#include "ArithmeticLogicUnit.hpp"

namespace Virtual{

ALU_HIVE::ALU_HIVE(ptr_t toggle, ptr8_t operation, ptr8_t carryRegister,  ptr32_t inputA, ptr32_t inputB) {
  input_pointers_[0] = toggle;
  byte_input_pointers_[0] = operation;
  byte_input_pointers_[1] = carryRegister;
  word_input_pointers_[1] = inputA;
  word_input_pointers_[2] = inputB;
  
  circuit_components_[0] = std::make_shared<ByteSplitter>(operation); // TODO: rewire
  circuit_components_[1] = std::make_shared<FourBitDecoder>(
				circuit_components_[0]->release_output(0),
				circuit_components_[0]->release_output(1),
				circuit_components_[0]->release_output(2),
				circuit_components_[0]->release_output(3));
  circuit_components_[2] = std::make_shared<ByteSplitter>(carryRegister); // TODO: rewire
  // 0 NOT
  circuit_components_[3] = std::make_shared<WordNot>(inputA); // TODO; rewire
  circuit_components_[4] = std::make_shared<ToggledWord>(
		  		circuit_components_[4]->release_word_output(0),
				circuit_components_[1]->release_output(0) ); // 4 is new global output
  // 1 AND
  circuit_components_[5] = std::make_shared<WordAnd>(inputA,inputB); // TODO: rewire
  circuit_components_[6] = std::make_shared<ToggledWord>(
		  		circuit_components_[5]->release_word_output(0),
				circuit_components_[1]->release_output(1) );
  circuit_components_[6]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 2 NAND
  circuit_components_[7] = std::make_shared<WordNAND>(inputA,inputB); // TODO: rewire
  circuit_components_[8] = std::make_shared<ToggledWord>(
				circuit_components_[7]->release_word_output(0),
				circuit_components_[1]->release_ouput(2) );
  circuit_components_[8]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 3 OR
  circuit_components_[9] = std::make_shared<WordOr>(inputA, inputB); // TODO: rewire
  circuit_components_[10] = std::make_shared<ToggledWord>(
		  		circuit_components_[9]->release_word_output(0),
				circuit_components_[1]->release_output(3) );
  circuit_components_[10]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 4 Nor
  circuit_components_[11] = std::make_shared<WordNor>(inputA, inputB); // TODO: rewire
  circuit_components_[12] = std::make_shared<ToggledWord>(
		  		circuit_components_[11]->release_word_output(0),
				circuit_components_[1]->release_output(4) );
  circuit_components_[12]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 5 Xor
  circuit_components_[13] = std::make_shared<WordXor>(inputA, inputB); // TODO: rewire
  circuit_components_[14] = std::make_shared<ToggledWord(
		  		circuit_components_[13]->release_word_output(0),
				circuit_components_[1]->release_ouput(5));
  circuit_components_[14]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 6 BIC (just A And (Not B))
  circuit_components_[15] = std::make_shared<WordNot>(inputB); // TODO: rewire
  circuit_components_[16] = std::make_shared<WordAnd>(
		  		inputA,
		  		circuit_components_[15]->release_word_output(0)); // TODO: rewire
  circuit_components_[17] = std::make_shared<ToggledWord>(
		  		circuit_components_[16]->release_word_output(0),
				circuit_components_[1]->release_output(6));
  circuit_components_[17]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 7 ADD
  circuit_components_[18] = std::make_shared<WordAdder>();
  circuit_components_[18]->connect_word_input(inputA,0); // TODO: rewire
  circuit_components_[18]->connect_word_input(inputB,1); // TODO: rewire
  circuit_components_[19] = std::make_shared<ToggledWord>(
		  		circuit_components_[17]->release_word_output(0),
				circuit_components_[1]->release_output(7) );
  circuit_components_[19]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 8 ADC
  circuit_components_[20] = std::make_shared<WordAdder>(
		  		circuit_components_[2]->release_output(0),
				inputA, inputB); // TODO; rewire, TODO: connect ByteMaker&ByteOr the input carry
						 // 			for carry out
  circuit_components_[21] = std::make_shared<ToggledWord>(
		  		circuit_components_[20]->release_word_output(0),
				circuit_components_[1]->release_output(8));
  circuit_components_[21]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 9 SUB
  circuit_components_[22] = std::make_shared<WordNeg>(inputB); // TODO: rewire
  circuit_components_[23] = std::make_shared<WordAdder>(
		  		inputA,
				circuit_components_[22]->release_word_output(0)); // TODO: rewire
  circuit_components_[24] = std::make_shared<ToggledWord>(
		  		circuit_components_[23]->release_word_output(0),
				circuit_components_[1]->release_output(9));
  circuit_components_[24]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 10 SBC (takes some work for flag computations)
  circuit_components_[25] = std::make_shared<WordNot>(inputB); // TODO: rewire
  circuit_components_[26] = std::make_shared<WordAdder>(
		  		circuit_components_[2]->release_output(0),
				inputA,
				circuit_components_[25]->release_word_output(0)); // TODO: rewire, TODO: connect
										  // 		ByteMaker for carryout
  circuit_components_[27] = std::make_shared<WordSF>(inputA); // TODO: rewire
  circuit_components_[28] = std::make_shared<WordSF>(inputB); // TODO: rewire
  circuit_components_[29] = std::make_shared<WordSF>(circuit_components_[26]->release_word_output(0));
  circuit_components_[30] = std::make_shared<Xor>(
		  		circuit_components_[27]->release_output(0),
				circuit_components_[28]->release_output(0));
  circuit_components_[31] = std::make_shared<Xor>(
		  		circuit_components_[27]->release_output(0),
				circuit_components_[29]->release_output(0));
  circuit_components_[32] = std::make_shared<And>(
		  		circuit_components_[30]->release_output(0),
				circuit_components_[31]->release_output(0)); // TODO: this is the overflow bit
  circuit_components_[33] = std::make_shared<ToggledWord>(
		  		circuit_components_[26]->release_word_output(0),
				circuit_components_[1]->release_output(10));
  circuit_components_[33]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 11 RSB (=-SUB)
  circuit_components_[34] = std::make_shared<WordNeg>(circuit_components_[23]->release_word_output(0));
  circuit_components_[35] = std::make_shared<ToggledWord>(
		 		circuit_components_[34]->release_word_output(0),
			        circuit_components_[1]->release_output(11));
  circuit_components_[35]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 12 RSC
  circuit_components_[36] = std::make_shared<WordAdder>(
				circuit_components_[2]->release_output(0),
			        inputB,
				circuit_components_[3]->release_word_output(0)); // TODO: rewire, carry bit, overflow
										 //       same as SBC?
  circuit_components_[37] = std::make_shared<ToggledWord>(
		  		circuit_components_[36]->release_word_output(0),
				circuit_components_[1]->release_output(12));
  circuit_components_[37]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 13 ASR






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
