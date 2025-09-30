#include "SourceDestDecoder.hpp"

namespace Virtual{

SourceDestDecoderHIVE::SourceDestDecoderHIVE(ptr32_t input) {
  word_input_pointers_[0] = input;
  circuit_components_[0] = std::make_shared<WordByter>(input);
  // Mode Byte (ByteD)
  circuit_components_[1] = std::make_shared<ByteSplitter>(
		  		circuit_components_[0]->release_byte_output(3));
  // Source Byte (ByteC)
  circuit_components_[2] = std::make_shared<ByteSplitter>(
		  		circuit_components_[0]->release_byte_output(2));
  // Dest Byte (ByteB)
  circuit_components_[3] = std::make_shared<ByteSplitter>(
		  		circuit_components_[0]->release_byte_output(1));

  circuit_components_[4] = std::make_shared<ThreeBitDecoder>(
		  		circuit_components_[1]->release_output(0),
				circuit_components_[1]->release_output(1),
				circuit_components_[1]->release_output(2));
  output_pointers_[0] = circuit_components_[4]->release_output(0);
  output_pointers_[1] = circuit_components_[4]->release_output(1);
  output_pointers_[2] = circuit_components_[4]->release_output(2);
  output_pointers_[3] = circuit_components_[4]->release_output(3);
  output_pointers_[4] = circuit_components_[4]->release_output(4);
  output_pointers_[5] = circuit_components_[4]->release_output(7);
  output_pointers_[6] = circuit_components_[1]->release_output(5);
  output_pointers_[7] = circuit_components_[1]->release_output(6);
  output_pointers_[8] = circuit_components_[1]->release_output(7);

  circuit_components_[5] = std::make_shared<FiveBitDecoder>(
		  		circuit_components_[2]->release_output(0),
				circuit_components_[2]->release_output(1),
				circuit_components_[2]->release_output(2),
				circuit_components_[2]->release_output(3),
				circuit_components_[2]->release_output(4));
  output_pointers_[9] = circuit_components_[5]->release_output(0);
  output_pointers_[10] = circuit_components_[5]->release_output(1);
  output_pointers_[11] = circuit_components_[5]->release_output(2);
  output_pointers_[12] = circuit_components_[5]->release_output(3);
  output_pointers_[13] = circuit_components_[5]->release_output(4);
  output_pointers_[14] = circuit_components_[5]->release_output(5);
  output_pointers_[15] = circuit_components_[5]->release_output(6);
  output_pointers_[16] = circuit_components_[5]->release_output(7);
  output_pointers_[17] = circuit_components_[5]->release_output(8);
  output_pointers_[18] = circuit_components_[5]->release_output(9);
  output_pointers_[19] = circuit_components_[5]->release_output(10);
  output_pointers_[20] = circuit_components_[5]->release_output(11);
  output_pointers_[21] = circuit_components_[5]->release_output(12);	  
  output_pointers_[22] = circuit_components_[5]->release_output(13);
  output_pointers_[23] = circuit_components_[5]->release_output(14);
  output_pointers_[24] = circuit_components_[5]->release_output(15);
  output_pointers_[25] = circuit_components_[5]->release_output(16);
  output_pointers_[26] = circuit_components_[2]->release_output(7);

  circuit_components_[6] = std::make_shared<FiveBitDecoder>(
		  		circuit_components_[3]->release_output(0),
				circuit_components_[3]->release_output(1),
				circuit_components_[3]->release_output(2),
				circuit_components_[3]->release_output(3),
				circuit_components_[3]->release_output(4));
  output_pointers_[27] = circuit_components_[6]->release_output(0);
  output_pointers_[28] = circuit_components_[6]->release_output(1);
  output_pointers_[29] = circuit_components_[6]->release_output(2);
  output_pointers_[30] = circuit_components_[6]->release_output(3);
  output_pointers_[31] = circuit_components_[6]->release_output(4);
  output_pointers_[32] = circuit_components_[6]->release_output(5);
  output_pointers_[33] = circuit_components_[6]->release_output(6);
  output_pointers_[34] = circuit_components_[6]->release_output(7);
  output_pointers_[35] = circuit_components_[6]->release_output(8);
  output_pointers_[36] = circuit_components_[6]->release_output(9);
  output_pointers_[37] = circuit_components_[6]->release_output(10);
  output_pointers_[38] = circuit_components_[6]->release_output(11);
  output_pointers_[39] = circuit_components_[6]->release_output(12);	  
  output_pointers_[40] = circuit_components_[6]->release_output(13);
  output_pointers_[41] = circuit_components_[6]->release_output(14);
  output_pointers_[42] = circuit_components_[6]->release_output(15);
  output_pointers_[43] = circuit_components_[6]->release_output(16);
  output_pointers_[44] = circuit_components_[6]->release_output(17);
  output_pointers_[45] = circuit_components_[3]->release_output(7);
  // New
  circuit_components_[7] = std::make_shared<ByteSplitter>(
		  circuit_components_[0]->release_byte_output(0));
  output_pointers_[46] = circuit_components_[7]->release_output(5);
  output_pointers_[47] = circuit_components_[7]->release_output(6);
}

void SourceDestDecoderHIVE::rewire_input() {
  circuit_components_[0]->connect_word_input(word_input_pointers_[0],0);
}

const std::string SourceDestDecoderHIVE::gate_name = "SourceDestDecoderHIVE";

} //namespace Virtual
