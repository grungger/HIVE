// 11a - Counting Signals
#include "circuit.hpp"
#include "xor.hpp"
#include "and.hpp"
#include "or.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class CountingSignals : public Circuit<4,0,0,3,0,0> {
  public:
    CountingSignals() {
      this->init();
      this->components_.push_back(
		std::make_shared<And>(	(this->bit_cin_[0])->release_output(0),
					(this->bit_cin_[1])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<Xor>(	(this->bit_cin_[0])->release_output(0),
					(this->bit_cin_[1])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<And>(	(this->bit_cin_[2])->release_output(0),
					(this->bit_cin_[3])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<Xor>(	(this->bit_cin_[2])->release_output(0),
					(this->bit_cin_[3])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<And>(	(this->components_[1])->release_output(0),
					(this->components_[3])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<Xor>(	(this->components_[1])->release_output(0),
					(this->components_[3])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<Xor>(	(this->components_[0])->release_output(0),
					(this->components_[2])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<And>(	(this->components_[0])->release_output(0),
					(this->components_[2])->release_output(0) ) );
      this->components_.push_back(
		std::make_shared<Or>(	(this->components_[4])->release_output(0),
					(this->components_[6])->release_output(0) ) );
      this->bit_cout_[0]->connect_input(this->components_[5]->release_output(0), 0);
      this->bit_cout_[1]->connect_input(this->components_[8]->release_output(0), 0);
      this->bit_cout_[2]->connect_input(this->components_[7]->release_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

CountingSignals circuit = CountingSignals();
std::vector<bool> input{false,false,false,false};
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
input[0] = false;
input[1] = false;
input[2] = false;
input[3] = true;
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
std::string expectedOutput = std::string("000 100 100 010 100 010 010 110 ") +
						"100 010 010 110 010 110 110 001 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
