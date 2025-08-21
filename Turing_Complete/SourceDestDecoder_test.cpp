// 21a - Arithmetic Engine
#include "circuit.hpp"
#include "source_dest_decoder.hpp" 
#include <sstream>
#include <iostream>

using namespace Virtual;

class SourceDestDecoderTest : public Circuit<0,1,0,20,0,0> {
  public:
    SourceDestDecoderTest() {
      this->init();
      this->components_.push_back(
		std::make_shared<SourceDestDecoder>(
			(this->byte_cin_[0])->release_byte_output(0)));
      for (int i=0; i<20; i++) {
        (this->bit_cout_[i])->connect_input(
			this->components_[0]->release_output(i), 0);
      }
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
SourceDestDecoderTest circuit = SourceDestDecoderTest();
std::vector<std::uint8_t> input{0, 1, 7, 8, 56, 58, 63,127,191,255};
for (auto it=input.begin(); it!=input.end(); it++) {
  std::vector<std::uint8_t> ins{(*it)};
  circuit.tick(ins);
}
std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("10000000100000001000 01000000100000001000 00000001100000001000 10000000010000001000 10000000000000011000 00100000000000011000 00000001000000011000 00000001000000010100 00000001000000010010 00000001000000010001 ");

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
