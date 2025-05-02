// 16a - Signed Negator
#include "circuit.hpp"
#include "not.hpp"
#include "word_not.hpp"
#include "word_adder.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class SignedNegator : public Circuit<0,1,0,0,1,0> {
  public:
    SignedNegator() {
      this->init();
      this->components_.push_back(
		std::make_shared<Not>(std::make_shared<bool>(false)));
      this->components_.push_back(
		std::make_shared<ByteNot>(
			(this->byte_cin_[0])->release_byte_output(0)));
      this->components_.push_back(
		std::make_shared<ByteAdder>(
			(this->components_[0])->release_output(0),
			(this->components_[1])->release_byte_output(0),
			std::make_shared<byte_t>(0)));
      this->byte_cout_[0]->connect_byte_input(
				this->components_[2]->release_byte_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

SignedNegator circuit = SignedNegator();
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
std::string expectedOutput = std::string("b133 b168 b236 b218 b193 b182 ") +
					 "b189 b153 b199 b148 b155 b172 " +
				 	 "b156 b245 b185 b139 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
