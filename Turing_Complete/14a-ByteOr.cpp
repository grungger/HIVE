// 14a - Byte Or
#include "circuit.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "or.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class ByteOr : public Circuit<0,2,0,0,1,0> {
  public:
    ByteOr() {
      this->init();
      this->components_.push_back(
		std::make_shared<ByteSplitter>(
			(this->byte_cin_[0])->release_byte_output(0)));
      this->components_.push_back(
		std::make_shared<ByteSplitter>(
			(this->byte_cin_[1])->release_byte_output(0)));
      for (int i=0; i<8; i++) {
        this->components_.push_back(
		std::make_shared<Or>(
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
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ByteOr circuit = ByteOr();
std::vector<std::uint8_t> input{28, 17};
circuit.tick(input);
input[0] = 178;
input[1] = 244;
circuit.tick(input);
input[0] = 54;
input[1] = 33;
circuit.tick(input);
input[0] = 116;
input[1] = 179;
circuit.tick(input);
input[0] = 155;
input[1] = 189;
circuit.tick(input);
input[0] = 34;
input[1] = 41;
circuit.tick(input);
input[0] = 120;
input[1] = 226;
circuit.tick(input);
input[0] = 0;
input[1] = 0;
circuit.tick(input);
input[0] = 4;
input[1] = 53;
circuit.tick(input);
input[0] = 132;
input[1] = 180;
circuit.tick(input);
input[0] = 138;
input[1] = 133;
circuit.tick(input);
input[0] = 171;
input[1] = 179;
circuit.tick(input);
input[0] = 84;
input[1] = 151;
circuit.tick(input);
input[0] = 108;
input[1] = 28;
circuit.tick(input);
input[0] = 111;
input[1] = 53;
circuit.tick(input);
input[0] = 84;
input[1] = 37;
circuit.tick(input);
input[0] = 43;
input[1] = 0;
circuit.tick(input);
input[0] = 77;
input[1] = 89;
circuit.tick(input);
input[0] = 11;
input[1] = 251;
circuit.tick(input);
input[0] = 32;
input[1] = 54;
circuit.tick(input);
input[0] = 9;
input[1] = 34;
circuit.tick(input);
input[0] = 142;
input[1] = 236;
circuit.tick(input);
input[1] = 73;
circuit.tick(input);
input[0] = 157;
input[1] = 31;
circuit.tick(input);
input[0] = 121;
input[1] = 134;
circuit.tick(input);
input[0] = 53;
input[1] = 30;
circuit.tick(input);
input[0] = 92;
input[1] = 46;
circuit.tick(input);
input[0] = 89;
input[1] = 238;
circuit.tick(input);
input[0] = 138;
input[1] = 37;
circuit.tick(input);
input[0] = 18;
input[1] = 202;
circuit.tick(input);
input[0] = 178;
input[1] = 156;
circuit.tick(input);
input[0] = 129;
input[1] = 80;
circuit.tick(input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b29 b246 b55 b247 b191 b43 b250 b0 ") +
				"b53 b180 b143 b187 b215 b124 b127 b117 " +
				"b43 b93 b251 b54 b43 b238 b207 b159 " + 
				"b255 b63 b126 b255 b175 b218 b190 b209 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
