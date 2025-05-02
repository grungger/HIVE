// 16c - Saving Gracefully
#include "circuit.hpp"
#include "not.hpp"
#include "toggledbit.hpp"
#include "delay.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class SavingGracefully : public Circuit<2,0,0,1,0,0> {
  public:
    SavingGracefully() {
      this->init();
      this->components_.push_back(
		std::make_shared<Not>(
			(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledBit>());
      this->components_.push_back(
		std::make_shared<ToggledBit>(
			(this->bit_cin_[1])->release_output(0),
			(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<Delay>(
			(this->components_[1])->release_output(0)));
      this->components_[1]->connect_input(
			(this->components_[3])->release_output(0), 0);
      this->components_[1]->connect_input(
			(this->components_[0])->release_output(0), 1);
      this->components_[2]->connect_output(
			(this->components_[1])->release_output(0));
      this->memory_components_.push_back(
			(this->components_[3]) );
      this->bit_cout_[0]->connect_input(
			this->components_[3]->release_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

SavingGracefully circuit = SavingGracefully();
std::vector<bool> input{true, true};
circuit.tick(input);
circuit.tick(input);
input[1] = false;
circuit.tick(input);
circuit.tick(input);
input[0] = false;
circuit.tick(input);
input[1] = true;
circuit.tick(input);
input[0] = true;
input[1] = false;
circuit.tick(input);
input[1] = true;
circuit.tick(input);
circuit.tick(input);
input[0] = false;
circuit.tick(input);
input[1] = false;
circuit.tick(input);
input[0] = true;
circuit.tick(input);
circuit.tick(input);


std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("0 1 1 0 0 0 0 0 1 1 1 1 0 ");

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
