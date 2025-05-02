// 17 - Saving Bytes
#include "circuit.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "bitmemory.hpp"
#include "toggledword.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class SavingBytes : public Circuit<2,1,0,0,1,0> {
  public:
    SavingBytes() {
      this->init();
      this->components_.push_back(
		std::make_shared<ByteSplitter>(
			(this->byte_cin_[0])->release_byte_output(0)));
      for (int i=0; i<8; i++) {
        this->components_.push_back(
		std::make_shared<BitMemory>(
			(this->bit_cin_[1])->release_output(0),
			(this->components_[0])->release_output(i)));
        this->memory_components_.push_back(
		this->components_[i+1] );
      }
      this->components_.push_back( std::make_shared<ByteMaker>() );
      for (int i=0; i<8; i++) {
        this->components_[9]->connect_input(
			(this->components_[i+1])->release_output(0), i);
      }
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[9])->release_byte_output(0),
			(this->bit_cin_[0])->release_output(0)));
      this->byte_cout_[0]->connect_byte_input(
			this->components_[10]->release_byte_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

SavingBytes circuit = SavingBytes();
std::vector<bool> inputb{false, true};
std::vector<std::uint8_t> input{17};
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 244;
circuit.tick(inputb, input);
inputb[0] = false;
inputb[1] = false;
input[0] = 33;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 179;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 189;
circuit.tick(inputb, input);
input[0] = 41;
circuit.tick(inputb, input);
input[0] = 226;
circuit.tick(inputb, input);
inputb[1] = true;
input[0] = 180;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 133;
circuit.tick(inputb, input);
inputb[1] = false;
input[0] = 179;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 151;
circuit.tick(inputb, input);
inputb[0] = true;
inputb[1] = true;
input[0] = 28;
circuit.tick(inputb, input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b0 b17 b17 b244 b244 b244 b244 ") +
					"b244 b180 b133 b133 b133 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
