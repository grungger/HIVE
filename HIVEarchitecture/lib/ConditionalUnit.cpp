#include "ConditionalUnit.hpp"

namespace Virtual{

ConditionalUnitHIVE::ConditionalUnitHIVE(ptr_t toggle, ptr8_t operation, ptr32_t inputA, ptr32_t inputB) {
  input_pointers_[0] = toggle;
  byte_input_pointers_[0] = operation;
  word_input_pointers_[0] = inputA;
  word_input_pointers_[1] = inputB;
  circuit_components_[0] = std::make_shared<ByteSplitter>(operation); 
  circuit_components_[1] = std::make_shared<FourBitDecoder>(
				circuit_components_[0]->release_output(0),
				circuit_components_[0]->release_output(1),
				circuit_components_[0]->release_output(2),
				circuit_components_[0]->release_output(3) );
  circuit_components_[2] = std::make_shared<Not>(); // always On output
  // 0 EQ A==B
  circuit_components_[3] = std::make_shared<WordNot>(inputB); 
  circuit_components_[4] = std::make_shared<WordAdder>(circuit_components_[2]->release_output(0), inputA, 
		  					circuit_components_[3]->release_word_output(0));
  circuit_components_[5] = std::make_shared<WordNot>(circuit_components_[4]->release_word_output(0));
  
  circuit_components_[6] = std::make_shared<WordAdder>(circuit_components_[2]->release_output(0), 
		  					circuit_components_[5]->release_word_output(0));
  circuit_components_[7] = std::make_shared<ToggledBit>(
		  		circuit_components_[6]->release_output(0),
				circuit_components_[1]->release_output(0)); // 7 is the new universal output
  // 1 NE A!=B
  circuit_components_[8] = std::make_shared<Not>( circuit_components_[6]->release_output(0) );
  circuit_components_[9] = std::make_shared<ToggledBit>(
		  		circuit_components_[8]->release_output(0),
				circuit_components_[1]->release_output(1));
  circuit_components_[9]->connect_output(
		 	circuit_components_[7]->release_output(0));
  // 2 GE A>=B
  circuit_components_[10] = std::make_shared<ToggledBit>(
		  		circuit_components_[4]->release_output(0),
				circuit_components_[1]->release_output(2));
  circuit_components_[10]->connect_output(
		  	circuit_components_[7]->release_output(0));
  // 3 G A>B
  circuit_components_[11] = std::make_shared<And>(
		  		circuit_components_[8]->release_output(0),
				circuit_components_[4]->release_output(0));
  circuit_components_[12] = std::make_shared<ToggledBit>(
		  		circuit_components_[11]->release_output(0),
				circuit_components_[1]->release_output(3));
  circuit_components_[12]->connect_output(
		 	circuit_components_[7]->release_output(0));
  // 4 LE A<=B
  circuit_components_[13] = std::make_shared<Not>( circuit_components_[11]->release_output(0) );
  circuit_components_[14] = std::make_shared<ToggledBit>( 
		  		circuit_components_[13]->release_output(0),
				circuit_components_[1]->release_output(4));
  circuit_components_[14]->connect_output(
		  	circuit_components_[7]->release_output(0));
  // 5 L A<B
  circuit_components_[15] = std::make_shared<Not>( circuit_components_[4]->release_output(0) );
  circuit_components_[16] = std::make_shared<ToggledBit>(
		  		circuit_components_[15]->release_output(0),
				circuit_components_[1]->release_output(5));
  circuit_components_[16]->connect_output(
		 	circuit_components_[7]->release_output(0)); 
  // 6 GES A>s=B ->compute overflow via AND(XOR(A[MSB], B[MSB]),XOR(A[MSB],(A-B)[MSB])) & SF as (A-B)[MSB] and XOR the two ->signed less
  circuit_components_[17] = std::make_shared<WordSF>(inputA); 
  circuit_components_[18] = std::make_shared<WordSF>(inputB); 
  circuit_components_[19] = std::make_shared<WordSF>(circuit_components_[4]->release_word_output(0));
  circuit_components_[20] = std::make_shared<Xor>(
		  		circuit_components_[17]->release_output(0),
				circuit_components_[18]->release_output(0));
  circuit_components_[21] = std::make_shared<Xor>(
		  		circuit_components_[17]->release_output(0),
				circuit_components_[19]->release_output(0));
  circuit_components_[22] = std::make_shared<And>(
		  		circuit_components_[20]->release_output(0),
				circuit_components_[21]->release_output(0));
  circuit_components_[23] = std::make_shared<Xor>(
		  		circuit_components_[19]->release_output(0),
				circuit_components_[22]->release_output(0)); // this is signed less than bit
  circuit_components_[24] = std::make_shared<Not>( circuit_components_[23]->release_output(0) );
  circuit_components_[25] = std::make_shared<ToggledBit>(
		  		circuit_components_[24]->release_output(0),
				circuit_components_[1]->release_output(6));
  circuit_components_[25]->connect_output( circuit_components_[7]->release_output(0) );
  // 7 GS A>sB
  circuit_components_[26] = std::make_shared<And>(
		  		circuit_components_[24]->release_output(0),
				circuit_components_[8]->release_output(0));
  circuit_components_[27] = std::make_shared<ToggledBit>(
		  		circuit_components_[26]->release_output(0),
				circuit_components_[1]->release_output(7));
  circuit_components_[27]->connect_output( circuit_components_[7]->release_output(0) );
  // 8 LES A<s=B
  circuit_components_[28] = std::make_shared<Not>(
		  		circuit_components_[26]->release_output(0));
  circuit_components_[29] = std::make_shared<ToggledBit>(
		  		circuit_components_[28]->release_output(0),
				circuit_components_[1]->release_output(8));
  circuit_components_[29]->connect_output( circuit_components_[7]->release_output(0) );
  // 9 LS A<sB
  circuit_components_[30] = std::make_shared<ToggledBit>(
		  		circuit_components_[23]->release_output(0),
				circuit_components_[1]->release_output(9));
  circuit_components_[30]->connect_output( circuit_components_[7]->release_output(0) );
  // 10 AL
  circuit_components_[31] = std::make_shared<ToggledBit>(
		  		circuit_components_[2]->release_output(0),
				circuit_components_[1]->release_output(10));
  circuit_components_[31]->connect_output( circuit_components_[7]->release_output(0) );
  // 11 N
  circuit_components_[32] = std::make_shared<ToggledBit>();
  circuit_components_[32]->connect_input( circuit_components_[1]->release_output(11), 1 );
  circuit_components_[32]->connect_output( circuit_components_[7]->release_output(0) );
  
  circuit_components_[33] = std::make_shared<ToggledBit>(
		  		circuit_components_[7]->release_output(0),
				toggle,
				true); // overwrite with zero if not toggled 
				       // (i.e. dont overwrite counter if not in conditional mode)
  output_pointers_[0] = circuit_components_[33]->release_output(0);
}

void ConditionalUnitHIVE::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
  circuit_components_[3]->connect_word_input(word_input_pointers_[1],0);
  circuit_components_[4]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[17]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[18]->connect_word_input(word_input_pointers_[1],0);
  circuit_components_[33]->connect_input(input_pointers_[0], 1);
}

const std::string ConditionalUnitHIVE::gate_name = "ConditionalUnitHIVE";

} //namespace Virtual
