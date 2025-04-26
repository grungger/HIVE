// 12a - Double the Number
#include "circuit.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class DoubleTheNumber : public Circuit<0,1,0,0,1,0> {
  public:
    DoubleTheNumber() {
      this->init();
      this->components_.push_back(
		std::make_shared<ByteSplitter>(
			(this->byte_cin_[0])->release_byte_output(0)));
      this->components_.push_back( std::make_shared<ByteMaker>() );
      for (int i=0; i<7; i++) {
        this->components_[1]->connect_input(
			(this->components_[0])->release_output(i), i+1);
      }
      this->byte_cout_[0]->connect_byte_input(
				this->components_[1]->release_byte_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

DoubleTheNumber circuit = DoubleTheNumber();
std::vector<std::uint8_t> input{123};
circuit.tick(input);
input[0] = 88;
circuit.tick(input);
input[0] = 20;
circuit.tick(input);
input[0] = 38;
circuit.tick(input);
input[0] = 63;
circuit.tick(input);
input[0] = 74;
circuit.tick(input);
input[0] = 67;
circuit.tick(input);
input[0] = 103;
circuit.tick(input);
input[0] = 57;
circuit.tick(input);
input[0] = 108;
circuit.tick(input);
input[0] = 101;
circuit.tick(input);
input[0] = 84;
circuit.tick(input);
input[0] = 100;
circuit.tick(input);
input[0] = 11;
circuit.tick(input);
input[0] = 71;
circuit.tick(input);
input[0] = 117;
circuit.tick(input);


std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b246 b176 b40 b76 b126 b148 b134 b206 ") +
				"b114 b216 b202 b168 b200 b22 b142 b234 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
