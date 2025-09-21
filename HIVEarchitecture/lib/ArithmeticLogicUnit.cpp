#include "ArithmeticLogicUnit.hpp"

namespace Virtual{

ALU_HIVE::ALU_HIVE(ptr_t toggle, ptr8_t operation, ptr8_t carryRegister,  ptr32_t inputA, ptr32_t inputB) {
  input_pointers_[0] = toggle;
  byte_input_pointers_[0] = operation;
  byte_input_pointers_[1] = carryRegister;
  word_input_pointers_[0] = inputA;
  word_input_pointers_[1] = inputB;
  
  circuit_components_[0] = std::make_shared<ByteSplitter>(operation);
  circuit_components_[1] = std::make_shared<FourBitDecoder>(
				circuit_components_[0]->release_output(0),
				circuit_components_[0]->release_output(1),
				circuit_components_[0]->release_output(2),
				circuit_components_[0]->release_output(3));
  circuit_components_[2] = std::make_shared<ByteSplitter>(carryRegister);
  // 0 NOT
  circuit_components_[3] = std::make_shared<WordNot>(inputA); 
  circuit_components_[4] = std::make_shared<ToggledWord>(
		  		circuit_components_[3]->release_word_output(0),
				circuit_components_[1]->release_output(0) ); // 4 is new global output
  // 1 AND
  circuit_components_[5] = std::make_shared<WordAnd>(inputA,inputB);
  circuit_components_[6] = std::make_shared<ToggledWord>(
		  		circuit_components_[5]->release_word_output(0),
				circuit_components_[1]->release_output(1) );
  circuit_components_[6]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 2 NAND
  circuit_components_[7] = std::make_shared<WordNAND>(inputA,inputB); 
  circuit_components_[8] = std::make_shared<ToggledWord>(
				circuit_components_[7]->release_word_output(0),
				circuit_components_[1]->release_output(2) );
  circuit_components_[8]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 3 OR
  circuit_components_[9] = std::make_shared<WordOr>(inputA, inputB); 
  circuit_components_[10] = std::make_shared<ToggledWord>(
		  		circuit_components_[9]->release_word_output(0),
				circuit_components_[1]->release_output(3) );
  circuit_components_[10]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 4 Nor
  circuit_components_[11] = std::make_shared<WordNor>(inputA, inputB); 
  circuit_components_[12] = std::make_shared<ToggledWord>(
		  		circuit_components_[11]->release_word_output(0),
				circuit_components_[1]->release_output(4) );
  circuit_components_[12]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 5 Xor
  circuit_components_[13] = std::make_shared<WordXor>(inputA, inputB); 
  circuit_components_[14] = std::make_shared<ToggledWord>(
		  		circuit_components_[13]->release_word_output(0),
				circuit_components_[1]->release_output(5));
  circuit_components_[14]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 6 BIC (just A And (Not B))
  circuit_components_[15] = std::make_shared<WordNot>(inputB); 
  circuit_components_[16] = std::make_shared<WordAnd>(
		  		inputA,
		  		circuit_components_[15]->release_word_output(0)); 
  circuit_components_[17] = std::make_shared<ToggledWord>(
		  		circuit_components_[16]->release_word_output(0),
				circuit_components_[1]->release_output(6));
  circuit_components_[17]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 7 ADD
  circuit_components_[18] = std::make_shared<WordAdder>();
  circuit_components_[18]->connect_word_input(inputA,0); 
  circuit_components_[18]->connect_word_input(inputB,1); 
  circuit_components_[19] = std::make_shared<ToggledWord>(
		  		circuit_components_[18]->release_word_output(0),
				circuit_components_[1]->release_output(7) );
  circuit_components_[19]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 8 ADC
  circuit_components_[20] = std::make_shared<WordAdder>(
		  		circuit_components_[2]->release_output(0),
				inputA, inputB); 
  circuit_components_[21] = std::make_shared<ToggledWord>(
		  		circuit_components_[20]->release_word_output(0),
				circuit_components_[1]->release_output(8));
  circuit_components_[21]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 9 SUB
  circuit_components_[22] = std::make_shared<WordNeg>(inputB); 
  circuit_components_[23] = std::make_shared<WordAdder>();
  circuit_components_[23]->connect_word_input(inputA,0);
  circuit_components_[23]->connect_word_input(
		  		circuit_components_[22]->release_word_output(0), 1);
  circuit_components_[24] = std::make_shared<ToggledWord>(
		  		circuit_components_[23]->release_word_output(0),
				circuit_components_[1]->release_output(9));
  circuit_components_[24]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 10 SBC (takes some work for flag computations)
  circuit_components_[25] = std::make_shared<WordNot>(inputB); 
  circuit_components_[26] = std::make_shared<WordAdder>(
		  		circuit_components_[2]->release_output(0),
				inputA,
				circuit_components_[25]->release_word_output(0)); 
  circuit_components_[27] = std::make_shared<WordSF>(inputA); 
  circuit_components_[28] = std::make_shared<WordSF>(inputB); 
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
				circuit_components_[3]->release_word_output(0)); 
  circuit_components_[37] = std::make_shared<ToggledWord>(
		  		circuit_components_[36]->release_word_output(0),
				circuit_components_[1]->release_output(12));
  circuit_components_[37]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // 13 ASR (decode the lowest five bits to compute B mod 32, then shift them by the appropriate amount)
  // 14 LSR
  // 15 LSL
  //   for future improvement the bit shift operators are implemented immensely space inefficient...
  circuit_components_[38] = std::make_shared<WordSplitter>(inputA); 
  circuit_components_[39] = std::make_shared<WordSplitter>(inputB); 
  circuit_components_[40] = std::make_shared<FiveBitDecoder>(
		  		circuit_components_[39]->release_output(0),
				circuit_components_[39]->release_output(1),
				circuit_components_[39]->release_output(2),
				circuit_components_[39]->release_output(3),
				circuit_components_[39]->release_output(4));
  for (int i=0; i<32; i++) {
    circuit_components_[41+i*6] = std::make_shared<WordMaker>();
    circuit_components_[41+i*6+1] = std::make_shared<WordMaker>(); 
    circuit_components_[41+i*6+2] = std::make_shared<WordMaker>(); 
    for (int j=0; j<32-i; j++) {
      circuit_components_[41+i*6]->connect_input(circuit_components_[38]->release_output(j+i),j);
      circuit_components_[41+i*6+1]->connect_input(circuit_components_[38]->release_output(j+i),j);
      circuit_components_[41+i*6+2]->connect_input(circuit_components_[38]->release_output(31-j-i),31-j);
    }
    for (int j=32-i; j<32; j++) {
      circuit_components_[41+i*6]->connect_input(circuit_components_[38]->release_output(31),j);
    }
    circuit_components_[41+i*6+3] = std::make_shared<ToggledWord>(
	    			circuit_components_[41+i*6]->release_word_output(0),
				circuit_components_[40]->release_output(i));
    circuit_components_[41+i*6+4] = std::make_shared<ToggledWord>(
	    			circuit_components_[41+i*6+1]->release_word_output(0),
				circuit_components_[40]->release_output(i));
    circuit_components_[41+i*6+5] = std::make_shared<ToggledWord>(
	    			circuit_components_[41+i*6+2]->release_word_output(0),
				circuit_components_[40]->release_output(i));
    if (i!=0) {
      circuit_components_[41+i*6+3]->connect_word_output(circuit_components_[44]->release_word_output(0));
      circuit_components_[41+i*6+4]->connect_word_output(circuit_components_[45]->release_word_output(0));
      circuit_components_[41+i*6+5]->connect_word_output(circuit_components_[46]->release_word_output(0));
    }
  }
  circuit_components_[233] = std::make_shared<ToggledWord>(
	  			circuit_components_[44]->release_word_output(0),
				circuit_components_[1]->release_output(13));
  circuit_components_[233]->connect_word_output(circuit_components_[4]->release_word_output(0));
  circuit_components_[234] = std::make_shared<ToggledWord>(
		  		circuit_components_[45]->release_word_output(0),
				circuit_components_[1]->release_output(14));
  circuit_components_[234]->connect_word_output(circuit_components_[4]->release_word_output(0));
  circuit_components_[235] = std::make_shared<ToggledWord>(
		  		circuit_components_[46]->release_word_output(0),
				circuit_components_[1]->release_output(15));
  circuit_components_[235]->connect_word_output(circuit_components_[4]->release_word_output(0));
  // Now comes the carry flag register outputting
  // Carry in 7 ADD
  circuit_components_[236] = std::make_shared<ToggledBit>(
		  		circuit_components_[18]->release_output(0),
				circuit_components_[1]->release_output(7));
  // Carry in 8 ADC
  circuit_components_[237] = std::make_shared<ToggledBit>(
		  		circuit_components_[20]->release_output(0),
				circuit_components_[1]->release_output(8));
  circuit_components_[237]->connect_output(circuit_components_[236]->release_output(0));
  // Borrow/Carry in 9 SUB
  circuit_components_[238] = std::make_shared<ToggledBit>(
		  		circuit_components_[23]->release_output(0),
				circuit_components_[1]->release_output(9));
  circuit_components_[238]->connect_output(circuit_components_[236]->release_output(0));
  // Borrow/Carry in 10 SBC
  circuit_components_[239] = std::make_shared<ToggledBit>(
		  		circuit_components_[26]->release_output(0),
				circuit_components_[1]->release_output(10));
  circuit_components_[239]->connect_output(circuit_components_[236]->release_output(0));
  // TODO: borrow flag for reverse subtraction (with carry) and overflow flag for all subtractions
  // Make the output carry flag byte
  circuit_components_[240] = std::make_shared<ByteMaker>(
		  		circuit_components_[236]->release_output(0)); // TODO: add overflow flag
  circuit_components_[241] = std::make_shared<ToggledByte>(
		  		circuit_components_[240]->release_byte_output(0),
				toggle); // TODO: rewire
  circuit_components_[242] = std::make_shared<ToggledWord>(
		  		circuit_components_[4]->release_word_output(0),
				toggle); // TODO: rewire
  
  byte_output_pointers_[0] = circuit_components_[241]->release_byte_output(0);
  word_output_pointers_[0] = circuit_components_[242]->release_word_output(0);
}

void ALU_HIVE::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
  circuit_components_[2]->connect_byte_input(byte_input_pointers_[1],0);
  circuit_components_[3]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[5]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[5]->connect_word_input(word_input_pointers_[1],1);
  circuit_components_[7]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[7]->connect_word_input(word_input_pointers_[1],1);
  circuit_components_[9]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[9]->connect_word_input(word_input_pointers_[1],1);
  circuit_components_[11]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[11]->connect_word_input(word_input_pointers_[1],1);
  circuit_components_[13]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[13]->connect_word_input(word_input_pointers_[1],1);
  circuit_components_[15]->connect_word_input(word_input_pointers_[1],0);
  circuit_components_[16]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[18]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[18]->connect_word_input(word_input_pointers_[1],1);
  circuit_components_[20]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[20]->connect_word_input(word_input_pointers_[1],1);
  circuit_components_[22]->connect_word_input(word_input_pointers_[1],0);
  circuit_components_[23]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[25]->connect_word_input(word_input_pointers_[1],0);
  circuit_components_[26]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[27]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[28]->connect_word_input(word_input_pointers_[1],0);
  circuit_components_[36]->connect_word_input(word_input_pointers_[1],0);
  circuit_components_[38]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[39]->connect_word_input(word_input_pointers_[1],0);
  circuit_components_[241]->connect_input(input_pointers_[0],0);
  circuit_components_[242]->connect_input(input_pointers_[0],0);
}

const std::string ALU_HIVE::gate_name = "ALU_HIVE";

} //namespace Virtual
