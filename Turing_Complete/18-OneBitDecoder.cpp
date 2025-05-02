// 18 - One Bit Decoder
#include "circuit.hpp"
#include "not.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class OneBitDecoder : public Circuit<1,0,0,2,0,0> {
  public:
    OneBitDecoder() {
      this->init();
      this->components_.push_back(
		std::make_shared<Not>(	
			( this->bit_cin_[0] )->release_output(0)));
      this->bit_cout_[0]->connect_input(
		this->components_[0]->release_output(0), 0);
      this->bit_cout_[1]->connect_input(
		this->bit_cin_[0]->release_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

OneBitDecoder circuit = OneBitDecoder();
std::vector<bool> input{false};
circuit.tick(input);
input[0] = true;
circuit.tick(input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "10 01 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
