// 12c - Odd Ticks
#include "circuit.hpp"
#include "not.hpp"
#include "or.hpp"
#include "delay.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class OddTicks : public Circuit<1,0,0,1,0,0> {
  public:
    OddTicks() {
      this->init();
      this->components_.push_back(
		std::make_shared<Not>() );
      this->components_.push_back(
		std::make_shared<Or>((this->components_[0])->release_output(0),
					(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<Delay>(( this->components_[1] )->release_output(0)));
      this->memory_components_.push_back( components_[2] );
      this->components_[0]->connect_input(this->components_[2]->release_output(0), 0);
      this->bit_cout_[0]->connect_input(this->components_[2]->release_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

OddTicks circuit = OddTicks();
std::vector<bool> input{false};
circuit.tick(input);
circuit.tick(input);
circuit.tick(input);
circuit.tick(input);
circuit.tick(input);
circuit.tick(input);
circuit.tick(input);
circuit.tick(input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "0 1 0 1 0 1 0 1 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
