// 06 - Second Tick
#include "circuit.hpp"
#include "and.hpp"
#include "not.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class SecondTick : public Circuit<2,0,0,1,0,0> {
  public:
    SecondTick() {
      this->init();
      this->components_.push_back(
		std::make_shared<Not>(	(this->bit_cin_[1])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<And>(	( this->bit_cin_[0] )->release_output(0),
					( this->components_[0] )->release_output(0)));
      this->bit_cout_[0]->connect_input(this->components_[1]->release_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

SecondTick circuit = SecondTick();
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
std::string expectedOutput = "0 1 0 0 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
