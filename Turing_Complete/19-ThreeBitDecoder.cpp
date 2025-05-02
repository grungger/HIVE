// 19 - Three Bit Decoder
#include "circuit.hpp"
#include "onebitdecoder.hpp"
#include "and3.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class ThreeBitDecoder : public Circuit<3,0,0,8,0,0> {
  public:
    ThreeBitDecoder() {
      this->init();
      this->components_.push_back(
		std::make_shared<OneBitDecoder>(
			(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<OneBitDecoder>(
			(this->bit_cin_[1])->release_output(0)));
      this->components_.push_back(
		std::make_shared<OneBitDecoder>(
			(this->bit_cin_[2])->release_output(0)));
      // Bit 1 (comp 3)
      this->components_.push_back(
		std::make_shared<And3>(
			(this->components_[0])->release_output(0),
			(this->components_[1])->release_output(0),
			(this->components_[2])->release_output(0)));
      // Bit 2 (comp 4)
      this->components_.push_back(
		std::make_shared<And3>(
			(this->components_[0])->release_output(1),
			(this->components_[1])->release_output(0),
			(this->components_[2])->release_output(0)));
      // Bit 3 (comp 5)
      this->components_.push_back(
		std::make_shared<And3>(
			(this->components_[0])->release_output(0),
			(this->components_[1])->release_output(1),
			(this->components_[2])->release_output(0)));
      // Bit 4 (comp 6)
      this->components_.push_back(
		std::make_shared<And3>(
			(this->components_[0])->release_output(1),
			(this->components_[1])->release_output(1),
			(this->components_[2])->release_output(0)));
      // Bit 5 (comp 7)
      this->components_.push_back(
		std::make_shared<And3>(
			(this->components_[0])->release_output(0),
			(this->components_[1])->release_output(0),
			(this->components_[2])->release_output(1)));
      // Bit 6 (comp 8)
      this->components_.push_back(
		std::make_shared<And3>(
			(this->components_[0])->release_output(1),
			(this->components_[1])->release_output(0),
			(this->components_[2])->release_output(1)));
      // Bit 7 (comp 9)
      this->components_.push_back(
		std::make_shared<And3>(
			(this->components_[0])->release_output(0),
			(this->components_[1])->release_output(1),
			(this->components_[2])->release_output(1)));
      // Bit 8 (comp 10)
      this->components_.push_back(
		std::make_shared<And3>(
			(this->components_[0])->release_output(1),
			(this->components_[1])->release_output(1),
			(this->components_[2])->release_output(1)));
      for (int i=0; i<8; i++) {
        this->bit_cout_[i]->connect_input(
		this->components_[i+3]->release_output(0), 0);
      }
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ThreeBitDecoder circuit = ThreeBitDecoder();
std::vector<bool> input{false,false,false};
circuit.tick(input);
input[0] = true;
circuit.tick(input);
input[0] = false;
input[1] = true;
circuit.tick(input);
input[0] = true;
circuit.tick(input);
input[0] = false;
input[1] = false;
input[2] = true;
circuit.tick(input);
input[0] = true;
circuit.tick(input);
input[0] = false;
input[1] = true;
circuit.tick(input);
input[0] = true;
circuit.tick(input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("10000000 01000000 00100000 ") +
					"00010000 00001000 00000100 " +
					"00000010 00000001 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
