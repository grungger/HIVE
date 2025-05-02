// 14b - Byte Not
#include "circuit.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "not.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class ByteNot : public Circuit<0,1,0,0,1,0> {
  public:
    ByteNot() {
      this->init();
      this->components_.push_back(
		std::make_shared<ByteSplitter>(
			(this->byte_cin_[0])->release_byte_output(0)));
      for (int i=0; i<8; i++) {
        this->components_.push_back(
		std::make_shared<Not>(
			(this->components_[0])->release_output(i)));
      }
      this->components_.push_back( std::make_shared<ByteMaker>() );
      for (int i=0; i<8; i++) {
        this->components_[9]->connect_input(
			(this->components_[i+1])->release_output(0), i);
      }
      this->byte_cout_[0]->connect_byte_input(
				this->components_[9]->release_byte_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteNot circuit = ByteNot();
std::vector<std::uint8_t> input{28};
circuit.tick(input);
input[0] = 17;
circuit.tick(input);
input[0] = 178;
circuit.tick(input);
input[0] = 244;
circuit.tick(input);
input[0] = 54;
circuit.tick(input);
input[0] = 33;
circuit.tick(input);
input[0] = 116;
circuit.tick(input);
input[0] = 179;
circuit.tick(input);
input[0] = 155;
circuit.tick(input);
input[0] = 189;
circuit.tick(input);
input[0] = 34;
circuit.tick(input);
input[0] = 41;
circuit.tick(input);
input[0] = 120;
circuit.tick(input);
input[0] = 226;
circuit.tick(input);
input[0] = 4;
circuit.tick(input);
input[0] = 53;
circuit.tick(input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b227 b238 b77 b11 b201 b222 b139 b76 ") +
				"b100 b66 b221 b214 b135 b29 b251 b202 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
