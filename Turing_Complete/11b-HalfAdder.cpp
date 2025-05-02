// 11b - Half Adder
#include "circuit.hpp"
#include "xor.hpp"
#include "and.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class HalfAdder : public Circuit<2,0,0,2,0,0> {
  public:
    HalfAdder() {
      this->init();
      this->components_.push_back(
		std::make_shared<Xor>(	( this->bit_cin_[0] )->release_output(0),
					( this->bit_cin_[1] )->release_output(0)));
      this->components_.push_back(
		std::make_shared<And>(	( this->bit_cin_[0] )->release_output(0),
					( this->bit_cin_[1] )->release_output(0)));
      this->bit_cout_[0]->connect_input(this->components_[0]->release_output(0), 0);
      this->bit_cout_[1]->connect_input(this->components_[1]->release_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

HalfAdder circuit = HalfAdder();
std::vector<bool> input{false,false};
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
std::string expectedOutput = "00 10 10 01 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
