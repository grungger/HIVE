// 16b - The Bus
#include "circuit.hpp"
#include "not.hpp"
#include "toggledword.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class TheBus : public Circuit<2,2,0,0,2,0> {
  public:
    TheBus() {
      this->init();
      this->components_.push_back(
		std::make_shared<Not>(
			(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<Not>(
			(this->bit_cin_[1])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->byte_cin_[0])->release_byte_output(0),
			(this->components_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->byte_cin_[1])->release_byte_output(0),
			(this->bit_cin_[0])->release_output(0)));
      this->components_[3]->connect_byte_output(
			(this->components_[2])->release_byte_output(0));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[2])->release_byte_output(0),
			(this->components_[1])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[2])->release_byte_output(0),
			(this->bit_cin_[1])->release_output(0)));
      this->byte_cout_[0]->connect_byte_input(
			this->components_[4]->release_byte_output(0), 0);
      this->byte_cout_[1]->connect_byte_input(
			this->components_[5]->release_byte_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

TheBus circuit = TheBus();
std::vector<bool> inputb{true,false};
std::vector<std::uint8_t> input{0,20};
circuit.tick(inputb, input);
inputb[0] = false;
inputb[1] = true;
input[0] = 202;
circuit.tick(inputb, input);
inputb[0] = true;
input[1] = 185;
circuit.tick(inputb, input);
inputb[0] = false;
inputb[1] = false;
input[0] = 84;
circuit.tick(inputb, input);
input[0] = 199;
circuit.tick(inputb, input);
inputb[0] = true;
input[1] = 209;
circuit.tick(inputb, input);
inputb[1] = true;
circuit.tick(inputb, input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b20b0 b20b202 b20b185 ") +
				"b84b185 b199b185 b209b185 b209b209 "; 

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
