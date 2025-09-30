#include "RAM.hpp"

namespace Virtual{
// relevant opcodes: 4th byte of opcode i.e. wordByter output 3 is the instruction byte 
//   with values 2 for COMPUTE mode and 3 for COPY mode as well as bits 32 and 64
//   to determine whether the 2nd byte and/or the 3rd byte are RAM adresses respectively.
// Note: Usually one writes binary representation from left to right starting with highest bit,
//   therefore the naming A and B for the 3rd and 2nd byte respectively comes from this way of reading.
// Note: If neither A_isRAM nor B_isRAM nothing happens
RAM::RAM(ptr_t computeCopyToggle, ptr_t AloadToggle, ptr_t Btoggle, ptr8_t Aaddress, ptr8_t Baddress, ptr32_t general_channel) {
  // Initialize RAM with zeroes
  RAM_lines_.fill(0);

  input_pointers_[0] = computeCopyToggle;
  input_pointers_[1] = AloadToggle;
  input_pointers_[2] = Btoggle;
  byte_input_pointers_[0] = Aaddress;
  byte_input_pointers_[1] = Baddress;
  word_input_pointers_[0] = general_channel;

  // COMPUTE options for B
  circuit_components_[0] = std::make_shared<Not>( computeCopyToggle );
  circuit_components_[1] = std::make_shared<And>(
		  		circuit_components_[0]->release_output(0),
				Btoggle );
  // COPY options for B
  circuit_components_[2] = std::make_shared<And>(
		  		computeCopyToggle,
				Btoggle );

  auto ptrAaddress = std::shared_ptr<word_t>(&RAM_lines_[static_cast<int>((Aaddress)->value)], [](word_t*){} );
  circuit_components_[3] = std::make_shared<ToggledWord>( ptrAaddress, AloadToggle );

  auto ptrBaddress = std::shared_ptr<word_t>(&RAM_lines_[static_cast<int>((Baddress)->value)], [](word_t*){} );
  circuit_components_[4] = std::make_shared<ToggledWord>(ptrBaddress,
		  					circuit_components_[1]->release_output(0));
  // Now treat COPY mode, i.e. writing to B address
  circuit_components_[5] = std::make_shared<ToggledWord>(general_channel,
		  					circuit_components_[2]->release_output(0));
  circuit_components_[5]->connect_word_output(ptrBaddress);

  // A output (if COPY mode and A_isRAM or if COMPUTE mode and A_isRAM)
  word_output_pointers_[0] = circuit_components_[3]->release_word_output(0);
  // B output (if COMPUTE mode and B_isRAM)
  word_output_pointers_[1] = circuit_components_[4]->release_word_output(0);
}

void RAM::full_compute() {
  auto ptrAaddress = std::shared_ptr<word_t>(&RAM_lines_[static_cast<int>((byte_input_pointers_[0])->value)], [](word_t*){} );
  circuit_components_[3]->connect_word_input(ptrAaddress,0);

  auto ptrBaddress = std::shared_ptr<word_t>(&RAM_lines_[static_cast<int>((byte_input_pointers_[1])->value)], [](word_t*){} );
  circuit_components_[4]->connect_word_input(ptrBaddress,0);
  circuit_components_[5]->connect_word_output(ptrBaddress);

  for (int i=0; i<6; i++) {
    circuit_components_[i]->compute_output();
  }
}

void RAM::compute_output() {
  auto ptrBaddress = std::shared_ptr<word_t>(&RAM_lines_[static_cast<int>((byte_input_pointers_[1])->value)], [](word_t*){} );
  circuit_components_[5]->connect_word_output(ptrBaddress);
  circuit_components_[2]->compute_output();
  circuit_components_[5]->compute_output();
}

void RAM::rewire_input() {
  circuit_components_[0]->connect_input(input_pointers_[0],0);
  circuit_components_[1]->connect_input(input_pointers_[2],1);
  circuit_components_[2]->connect_input(input_pointers_[0],0);
  circuit_components_[2]->connect_input(input_pointers_[2],1);
  circuit_components_[3]->connect_input(input_pointers_[1],0);
  circuit_components_[5]->connect_word_input(word_input_pointers_[0],0);
}

void RAM::memory_release() {
  auto ptrAaddress = std::shared_ptr<word_t>(&RAM_lines_[static_cast<int>((byte_input_pointers_[0])->value)], [](word_t*){} );
  circuit_components_[3]->connect_word_input(ptrAaddress,0);

  auto ptrBaddress = std::shared_ptr<word_t>(&RAM_lines_[static_cast<int>((byte_input_pointers_[1])->value)], [](word_t*){} );
  circuit_components_[4]->connect_word_input(ptrBaddress,0);
  for (int i=0; i<5; i++) {
    circuit_components_[i]->compute_output();
  }
}

void RAM::connect_word_output_i(ptr32_t conOut, bool index) {
  int i = static_cast<int>(index);
  word_output_pointers_[i] = conOut;
  circuit_components_[3+static_cast<int>(index)]->connect_word_output(conOut);
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
