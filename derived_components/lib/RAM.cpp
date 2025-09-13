#include "RAM.hpp"

namespace Virtual{
// relevant opcodes: 4th byte of opcode i.e. wordByter output 3 is the instruction byte 
//   with values 2 for COMPUTE mode and 3 for COPY mode as well as bits 32 and 64
//   to determine whether the 2nd byte and/or the 3rd byte are RAM adresses respectively.
// Note: Usually one writes binary representation from left to right starting with highest bit,
//   therefore the naming A and B for the 3rd and 2nd byte respectively comes from this way of reading.
// Note: If neither A_isRAM nor B_isRAM nothing happens
RAM::RAM(ptr32_t full_opcode, ptr32_t general_channel) {
  // Initialize RAM with zeroes
  RAM_lines_.fill(0);

  word_input_pointers_[0] = full_opcode;
  word_input_pointers_[1] = general_channel;

  circuit_components_[0] = std::make_shared<WordByter>(full_opcode);
  circuit_components_[1] = std::make_shared<ByteDecoder>(circuit_components_[0]->release_byte_output(3));
  // COMPUTE and COPY options for A
  circuit_components_[2] = std::make_shared<Or3>(
		  		circuit_components_[1]->release_output(66),
				circuit_components_[1]->release_output(98),
				circuit_components_[1]->release_output(67) );
  circuit_components_[3] = std::make_shared<Or>(
		  		circuit_components_[2]->release_output(0),
				circuit_components_[1]->release_output(99) );
  // COMPUTE options for B
  circuit_components_[4] = std::make_shared<Or>(
		  		circuit_components_[1]->release_output(34),
				circuit_components_[1]->release_output(98) );
  // COPY options for B
  circuit_components_[5] = std::make_shared<Or>(
		  		circuit_components_[1]->release_output(35),
				circuit_components_[1]->release_output(99) );
  circuit_components_[6] = std::make_shared<ToggledWord>(std::make_shared<word_t>(RAM_lines_[static_cast<int>((circuit_components_[0]->release_byte_output(2))->value)]),
		  					circuit_components_[3]->release_output(0));
  circuit_components_[7] = std::make_shared<ToggledWord>(std::make_shared<word_t>(RAM_lines_[static_cast<int>((circuit_components_[0]->release_byte_output(1))->value)]),
		  					circuit_components_[4]->release_output(0));
  // Now treat COPY mode, i.e. writing to B address
  circuit_components_[8] = std::make_shared<ToggledWord>(general_channel,
		  					circuit_components_[5]->release_output(0));
  circuit_components_[8]->connect_word_output(std::make_shared<word_t>(RAM_lines_[static_cast<int>((circuit_components_[0]->release_byte_output(1))->value)]));

  // A output (if COPY mode and A_isRAM or if COMPUTE mode and A_isRAM)
  word_output_pointers_[0] = circuit_components_[6]->release_word_output(0);
  // B output (if COMPUTE mode and B_isRAM)
  word_output_pointers_[1] = circuit_components_[7]->release_word_output(0);
}

void RAM::compute_output() {
  circuit_components_[0]->compute_output();
  circuit_components_[8]->connect_word_output(std::make_shared<word_t>(RAM_lines_[static_cast<int>((circuit_components_[0]->release_byte_output(1))->value)]));
  for (int i=1; i<9; i++) { 
    circuit_components_[i]->compute_output();
  }
}

void RAM::rewire_input() {
  circuit_components_[0]->connect_word_input(word_input_pointers_[0],0);
  circuit_components_[8]->connect_word_input(word_input_pointers_[1],0);
}

void RAM::printRAM() {
  for (int i=0; i<16; i++) {
    for (int j=0; j<16; j++) {
      std::cout << RAM_lines_[16*i + j] << " ";
    }
    std::cout << "\n";
  }
}


const std::string RAM::gate_name = "RAM";

} //namespace Virtual
