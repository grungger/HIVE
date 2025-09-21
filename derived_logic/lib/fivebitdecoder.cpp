#include "fivebitdecoder.hpp"

namespace Virtual{

FiveBitDecoder::FiveBitDecoder(ptr_t in1, ptr_t in2, ptr_t in4, ptr_t in8, ptr_t in16) {
  input_pointers_[0] = in1;
  input_pointers_[1] = in2;
  input_pointers_[2] = in4;
  input_pointers_[3] = in8;
  input_pointers_[4] = in16;
  circuit_components_[0] = std::make_shared<FourBitDecoder>(in1,in2,in4,in8);
  circuit_components_[1] = std::make_shared<OneBitDecoder>(in16);

  circuit_components_[2] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(0),
				circuit_components_[1]->release_output(0));
  circuit_components_[3] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(1),
				circuit_components_[1]->release_output(0));
  circuit_components_[4] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(2),
				circuit_components_[1]->release_output(0));
  circuit_components_[5] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(3),
				circuit_components_[1]->release_output(0));
  circuit_components_[6] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(4),
				circuit_components_[1]->release_output(0));
  circuit_components_[7] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(5),
				circuit_components_[1]->release_output(0));
  circuit_components_[8] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(6),
				circuit_components_[1]->release_output(0));
  circuit_components_[9] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(7),
				circuit_components_[1]->release_output(0));
  circuit_components_[10] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(8),
				circuit_components_[1]->release_output(0));
  circuit_components_[11] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(9),
				circuit_components_[1]->release_output(0));
  circuit_components_[12] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(10),
				circuit_components_[1]->release_output(0));
  circuit_components_[13] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(11),
				circuit_components_[1]->release_output(0));
  circuit_components_[14] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(12),
				circuit_components_[1]->release_output(0));
  circuit_components_[15] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(13),
				circuit_components_[1]->release_output(0));
  circuit_components_[16] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(14),
				circuit_components_[1]->release_output(0));
  circuit_components_[17] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(15),
				circuit_components_[1]->release_output(0));
  circuit_components_[18] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(0),
				circuit_components_[1]->release_output(1));
  circuit_components_[19] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(1),
				circuit_components_[1]->release_output(1));
  circuit_components_[20] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(2),
				circuit_components_[1]->release_output(1));
  circuit_components_[21] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(3),
				circuit_components_[1]->release_output(1));
  circuit_components_[22] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(4),
				circuit_components_[1]->release_output(1));
  circuit_components_[23] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(5),
				circuit_components_[1]->release_output(1));
  circuit_components_[24] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(6),
				circuit_components_[1]->release_output(1));
  circuit_components_[25] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(7),
				circuit_components_[1]->release_output(1));
  circuit_components_[26] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(8),
				circuit_components_[1]->release_output(1));
  circuit_components_[27] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(9),
				circuit_components_[1]->release_output(1));
  circuit_components_[28] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(10),
				circuit_components_[1]->release_output(1));
  circuit_components_[29] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(11),
				circuit_components_[1]->release_output(1));
  circuit_components_[30] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(12),
				circuit_components_[1]->release_output(1));
  circuit_components_[31] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(13),
				circuit_components_[1]->release_output(1));
  circuit_components_[32] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(14),
				circuit_components_[1]->release_output(1));
  circuit_components_[33] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(15),
				circuit_components_[1]->release_output(1));

  
  output_pointers_[0]  = circuit_components_[2] ->release_output(0);
  output_pointers_[1]  = circuit_components_[3] ->release_output(0);
  output_pointers_[2]  = circuit_components_[4] ->release_output(0);
  output_pointers_[3]  = circuit_components_[5] ->release_output(0);
  output_pointers_[4]  = circuit_components_[6] ->release_output(0);
  output_pointers_[5]  = circuit_components_[7] ->release_output(0);
  output_pointers_[6]  = circuit_components_[8] ->release_output(0);
  output_pointers_[7]  = circuit_components_[9] ->release_output(0);
  output_pointers_[8]  = circuit_components_[10]->release_output(0);
  output_pointers_[9]  = circuit_components_[11]->release_output(0);
  output_pointers_[10] = circuit_components_[12]->release_output(0);
  output_pointers_[11] = circuit_components_[13]->release_output(0);
  output_pointers_[12] = circuit_components_[14]->release_output(0);
  output_pointers_[13] = circuit_components_[15]->release_output(0);
  output_pointers_[14] = circuit_components_[16]->release_output(0);
  output_pointers_[15] = circuit_components_[17]->release_output(0);
  output_pointers_[16] = circuit_components_[18]->release_output(0);
  output_pointers_[17] = circuit_components_[19]->release_output(0);
  output_pointers_[18] = circuit_components_[20]->release_output(0);
  output_pointers_[19] = circuit_components_[21]->release_output(0);
  output_pointers_[20] = circuit_components_[22]->release_output(0);
  output_pointers_[21] = circuit_components_[23]->release_output(0);
  output_pointers_[22] = circuit_components_[24]->release_output(0);
  output_pointers_[23] = circuit_components_[25]->release_output(0);
  output_pointers_[24] = circuit_components_[26]->release_output(0);
  output_pointers_[25] = circuit_components_[27]->release_output(0);
  output_pointers_[26] = circuit_components_[28]->release_output(0);
  output_pointers_[27] = circuit_components_[29]->release_output(0);
  output_pointers_[28] = circuit_components_[30]->release_output(0);
  output_pointers_[29] = circuit_components_[31]->release_output(0);
  output_pointers_[30] = circuit_components_[32]->release_output(0);
  output_pointers_[31] = circuit_components_[33]->release_output(0);
}

void FiveBitDecoder::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[0]->connect_input(input_pointers_[1],1);
  circuit_components_[0]->connect_input(input_pointers_[2],2);
  circuit_components_[0]->connect_input(input_pointers_[3],3);
  circuit_components_[1]->connect_input(input_pointers_[4],0);
}

const std::string FiveBitDecoder::gate_name = "5BitDecoder";

} //namespace Virtual
