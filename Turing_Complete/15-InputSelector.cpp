// 15 - Input Selector
#include "circuit.hpp"
#include "not.hpp"
#include "toggledword.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class InputSelector : public Circuit<1,2,0,0,1,0> {
  public:
    InputSelector() {
      this->init();
      this->components_.push_back(
		std::make_shared<Not>(
			(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->byte_cin_[0])->release_byte_output(0),
			(this->components_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->byte_cin_[1])->release_byte_output(0),
			(this->bit_cin_[0])->release_output(0)));
      this->components_[2]->connect_byte_output(
			(this->components_[1])->release_byte_output(0));
      this->byte_cout_[0]->connect_byte_input(
				this->components_[1]->release_byte_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

InputSelector circuit = InputSelector();
std::vector<bool> inputb{false};
std::vector<std::uint8_t> input{255,255};
circuit.tick(inputb, input);
input[0] = 166;
input[1] = 63;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 195;
input[1] = 231;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 108;
input[1] = 229;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 100;
input[1] = 139;
circuit.tick(inputb, input);
input[0] = 245;
input[1] = 143;
circuit.tick(inputb, input);
input[0] = 160;
input[1] = 189;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 243;
input[1] = 199;
circuit.tick(inputb, input);
input[0] = 10;
input[1] = 42;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 76;
input[1] = 250;
circuit.tick(inputb, input);
input[0] = 188;
input[1] = 164;
circuit.tick(inputb, input);
input[0] = 219;
input[1] = 138;
circuit.tick(inputb, input);
input[0] = 137;
input[1] = 245;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 175;
input[1] = 165;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 239;
input[1] = 120;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 211;
input[1] = 142;
circuit.tick(inputb, input);


std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b255 b166 b231 b108 b139 b143 ") +
					 "b189 b243 b10 b250 b164 b138 " +
					 "b245 b175 b120 b211 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
