// 20c - Counter
#include "circuit.hpp"
#include "word_mux.hpp"
#include "word_memory.hpp"
#include "word_adder.hpp"
#include "not.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class Counter : public Circuit<1,1,0,0,1,0> {
  public:
    Counter() {
      this->init();
      this->components_.push_back(
		std::make_shared<Not>() );
      this->components_.push_back(
		std::make_shared<ByteAdder>() );
      this->components_.push_back(
		std::make_shared<ByteMUX>(
			(this->bit_cin_[0])->release_output(0),
			(this->components_[1])->release_byte_output(0),
			(this->byte_cin_[0])->release_byte_output(0)));
      this->components_.push_back(
		std::make_shared<ByteMemory>(
			(this->components_[0])->release_output(0),
			(this->components_[0])->release_output(0),
			(this->components_[2])->release_byte_output(0)));
      this->memory_components_.push_back(
		this->components_[3] );
      this->components_[1]->connect_input(
		this->components_[0]->release_output(0), 0);
      this->components_[1]->connect_byte_input(
		this->components_[3]->release_byte_output(0), 0);
      this->byte_cout_[0]->connect_byte_input(
		this->components_[3]->release_byte_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

Counter circuit = Counter();
std::vector<bool> inputb{false};
std::vector<std::uint8_t> input{0};
circuit.tick(inputb, input);
input[0] = 244;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 33;
circuit.tick(inputb, input);
input[0] = 179;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 189;
circuit.tick(inputb, input);
input[0] = 41;
circuit.tick(inputb, input);
input[0] = 226;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 53;
circuit.tick(inputb, input);
input[0] = 180;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 133;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 179;
circuit.tick(inputb, input);
input[0] = 151;
circuit.tick(inputb, input);


std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b0 b1 b2 b33 b179 b180 b181 b182 ") + 
					"b53 b180 b181 b179 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
