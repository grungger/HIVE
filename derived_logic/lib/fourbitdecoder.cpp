#include "fourbitdecoder.hpp"

namespace Virtual{

FourBitDecoder::FourBitDecoder(ptr_t in1, ptr_t in2, ptr_t in4, ptr_t in8) {
  input_pointers_[0] = in1;
  input_pointers_[1] = in2;
  input_pointers_[2] = in4;
  input_pointers_[3] = in8;
  circuit_components_[0] = std::make_shared<ThreeBitDecoder>(in1,in2,in4);
  circuit_components_[1] = std::make_shared<OneBitDecoder>(in8);

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
		  		circuit_components_[0]->release_output(0),
				circuit_components_[1]->release_output(1));
  circuit_components_[11] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(1),
				circuit_components_[1]->release_output(1));
  circuit_components_[12] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(2),
				circuit_components_[1]->release_output(1));
  circuit_components_[13] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(3),
				circuit_components_[1]->release_output(1));
  circuit_components_[14] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(4),
				circuit_components_[1]->release_output(1));
  circuit_components_[15] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(5),
				circuit_components_[1]->release_output(1));
  circuit_components_[16] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(6),
				circuit_components_[1]->release_output(1));
  circuit_components_[17] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(7),
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
}

void FourBitDecoder::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[0]->connect_input(input_pointers_[1],1);
  circuit_components_[0]->connect_input(input_pointers_[2],2);
  circuit_components_[1]->connect_input(input_pointers_[3],0);
}

const std::string FourBitDecoder::gate_name = "4BitDecoder";

} //namespace Virtual
