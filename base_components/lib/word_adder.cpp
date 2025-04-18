#include "word_adder.hpp"

namespace Virtual{

ByteAdder::ByteAdder(ptr_t inbit, ptr8_t sumA, ptr8_t sumB) {
  input_pointers_[0] = inbit;
  byte_input_pointers_[0] = sumA;
  byte_input_pointers_[1] = sumB;
  circuit_components_[0] = std::make_shared<ByteSplitter>(sumA);
  circuit_components_[1] = std::make_shared<ByteSplitter>(sumB);
  circuit_components_[2] = std::make_shared<FullAdder>(inbit, 
				circuit_components_[0]->release_output(0), 
				circuit_components_[1]->release_output(0));
  circuit_components_[3] = std::make_shared<FullAdder>(circuit_components_[2]->release_output(1), 
				circuit_components_[0]->release_output(1), 
				circuit_components_[1]->release_output(1));
  circuit_components_[4] = std::make_shared<FullAdder>(circuit_components_[3]->release_output(1),
				circuit_components_[0]->release_output(2),
				circuit_components_[1]->release_output(2));
  circuit_components_[5] = std::make_shared<FullAdder>(circuit_components_[4]->release_output(1),
				circuit_components_[0]->release_output(3),
				circuit_components_[1]->release_output(3));
  circuit_components_[6] = std::make_shared<FullAdder>(circuit_components_[5]->release_output(1),
				circuit_components_[0]->release_output(4),
				circuit_components_[1]->release_output(4));
  circuit_components_[7] = std::make_shared<FullAdder>(circuit_components_[6]->release_output(1),
				circuit_components_[0]->release_output(5),
				circuit_components_[1]->release_output(5));
  circuit_components_[8] = std::make_shared<FullAdder>(circuit_components_[7]->release_output(1),
				circuit_components_[0]->release_output(6),
				circuit_components_[1]->release_output(6));
  circuit_components_[9] = std::make_shared<FullAdder>(circuit_components_[8]->release_output(1),
				circuit_components_[0]->release_output(7),
				circuit_components_[1]->release_output(7));
  circuit_components_[10] = std::make_shared<ByteMaker>(circuit_components_[2]->release_output(0),
							circuit_components_[3]->release_output(0),
							circuit_components_[4]->release_output(0),
							circuit_components_[5]->release_output(0),
							circuit_components_[6]->release_output(0),
							circuit_components_[7]->release_output(0),
							circuit_components_[8]->release_output(0),
							circuit_components_[9]->release_output(0));
  byte_output_pointers_[0] = circuit_components_[10]->release_byte_output(0);
  output_pointers_[0] = circuit_components_[9]->release_output(1);
}

void ByteAdder::rewire_input() {
  circuit_components_[0]->connect_byte_input(byte_input_pointers_[0],0);
  circuit_components_[1]->connect_byte_input(byte_input_pointers_[1],0);
  circuit_components_[2]->connect_input(input_pointers_[0],0);
}

const std::string ByteAdder::gate_name = "ByteAdder";


// WordAdder section:

WordAdder::WordAdder(ptr_t inbit, ptr32_t inwordA, ptr32_t inwordB) {
  input_pointers_[0] = inbit;
  word_input_pointers_[0] = inwordA;
  word_input_pointers_[1] = inwordB;
  circuit_components_[0] = std::make_shared<WordSplitter>(inwordA);
  circuit_components_[1] = std::make_shared<WordSplitter>(inwordB);
  WordArg argA = circuit_components_[0]->release_wordarg_output();
  WordArg argB = circuit_components_[1]->release_wordarg_output();
  WordArg argC;
  circuit_components_[2] = std::make_shared<FullAdder>(
				inbit,
				argA.bits[0],
				argB.bits[0] );
  argC.bits[0] = circuit_components_[2]->release_output(0);
  for (int i=1; i<32; i++) {
    circuit_components_[i+2] = std::make_shared<FullAdder>(
				circuit_components_[i+1]->release_output(1),
				argA.bits[i],
				argB.bits[i] );
    argC.bits[i] = circuit_components_[i+2]->release_output(0);
  }
  circuit_components_[34] = std::make_shared<WordMaker>(argC);
  word_output_pointers_[0] = circuit_components_[34]->release_word_output(0);
  output_pointers_[0] = circuit_components_[33]->release_output(1);
}

void WordAdder::rewire_input() {
  circuit_components_[0]->connect_word_input(word_input_pointers_[0], 0);
  circuit_components_[1]->connect_word_input(word_input_pointers_[1], 0);
  circuit_components_[2]->connect_input(input_pointers_[0], 0);
}

const std::string WordAdder::gate_name = "WordAdder";

} //namespace Virtual
