// 09 - Xnor Gate
#include "circuit.hpp"
#include "xor.hpp"
#include "not.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class XnorGate : public Circuit<2,0,0,1,0,0> {
  public:
    XnorGate() {
      this->init();
      this->components_.push_back(
		std::make_shared<Xor>(	(this->bit_cin_[0])->release_output(0),
					(this->bit_cin_[1])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<Not>(	( this->components_[0] )->release_output(0) ));
      this->bit_cout_[0]->connect_input(this->components_[1]->release_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

XnorGate circuit = XnorGate();
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
std::string expectedOutput = "1 0 0 1 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
