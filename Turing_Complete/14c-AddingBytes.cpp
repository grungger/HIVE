// 14c - Adding Bytes
#include "circuit.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "full_adder.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class AddingBytes : public Circuit<1,2,0,1,1,0> {
  public:
    AddingBytes() {
      this->init();
      this->components_.push_back(
		std::make_shared<ByteSplitter>(
			(this->byte_cin_[0])->release_byte_output(0)));
      this->components_.push_back(
		std::make_shared<ByteSplitter>(
			(this->byte_cin_[1])->release_byte_output(0)));
      this->components_.push_back(
		std::make_shared<FullAdder>(
			(this->bit_cin_[0])->release_output(0),
			(this->components_[0])->release_output(0),
			(this->components_[1])->release_output(0)));
      for (int i=1; i<8; i++) {
        this->components_.push_back(
		std::make_shared<FullAdder>(
			(this->components_[i+1])->release_output(1),
			(this->components_[0])->release_output(i),
			(this->components_[1])->release_output(i)));
      }
      this->components_.push_back( std::make_shared<ByteMaker>() );
      for (int i=0; i<8; i++) {
        this->components_[10]->connect_input(
			(this->components_[i+2])->release_output(0), i);
      }
      this->byte_cout_[0]->connect_byte_input(
				this->components_[10]->release_byte_output(0), 0);
      this->bit_cout_[0]->connect_input(
				this->components_[9]->release_output(1), 0);
    }
};
      
int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

AddingBytes circuit = AddingBytes();
std::vector<bool> inputb{0};
std::vector<std::uint8_t> input{255,255};
circuit.tick(inputb, input);
input[0] = 166;
input[1] = 63;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 195;
input[1] = 231;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 108;
input[1] = 229;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 100;
input[1] = 139;
circuit.tick(inputb, input);
input[0] = 245;
input[1] = 143;
circuit.tick(inputb, input);
input[0] = 160;
input[1] = 189;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 243;
input[1] = 199;
circuit.tick(inputb, input);
input[0] = 10;
input[1] = 42;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 76;
input[1] = 250;
circuit.tick(inputb, input);
input[0] = 188;
input[1] = 164;
circuit.tick(inputb, input);
input[0] = 219;
input[1] = 138;
circuit.tick(inputb, input);
input[0] = 137;
input[1] = 245;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 175;
input[1] = 165;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 239;
input[1] = 120;
circuit.tick(inputb, input);
inputb[0] = false;
input[0] = 211;
input[1] = 142;
circuit.tick(inputb, input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("1b254 0b229 1b171 1b81 0b240 1b133 ") +
					 "1b94 1b186 0b52 1b71 1b97 1b102 " +
					 "1b127 1b84 1b104 1b97 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
