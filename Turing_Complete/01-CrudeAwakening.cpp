// 01 - Crude Awakening
#include "circuit.hpp"
#include "wire.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class CrudeAwakening : public Circuit<1,0,0,1,0,0> {
  public:
    CrudeAwakening() {
      this->init();
      this->components_.push_back(std::make_shared<Wire>((this->bit_cin_[0])->release_output(0)));
      this->bit_cout_[0]->connect_input(this->components_[0]->release_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

CrudeAwakening circuit = CrudeAwakening();
std::vector<bool> input{false};
circuit.tick(input);
input[0] = true;
circuit.tick(input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = "0 1 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
