// 21a - Arithmetic Engine
#include "circuit.hpp"
#include "word_splitter.hpp"
#include "word_or.hpp"
#include "word_not.hpp"
#include "word_nand.hpp"
#include "word_neg.hpp"
#include "word_adder.hpp"
#include "toggledword.hpp"
#include "threebitdecoder.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class ArithmeticEngine : public Circuit<0,3,0,0,1,0> {
  public:
    ArithmeticEngine() {
      this->init();
      this->components_.push_back(
		std::make_shared<ByteSplitter>(
			(this->byte_cin_[0])->release_byte_output(0)));
      this->components_.push_back(
		std::make_shared<ByteOr>(
			(this->byte_cin_[1])->release_byte_output(0),
			(this->byte_cin_[2])->release_byte_output(0)));
      // Components 2:
      this->components_.push_back(
		std::make_shared<ByteNAND>(
			(this->byte_cin_[1])->release_byte_output(0),
			(this->byte_cin_[2])->release_byte_output(0)));
      // Components 3:
      this->components_.push_back(
		std::make_shared<ThreeBitDecoder>(
			(this->components_[0])->release_output(0),
			(this->components_[0])->release_output(1),
			(this->components_[0])->release_output(2)));
      // Components 4:
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[1])->release_byte_output(0),
			(this->components_[3])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ByteNot>(
			(this->components_[1])->release_byte_output(0)));
      // Components 6:
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[5])->release_byte_output(0),
			(this->components_[3])->release_output(2)));
      this->components_[6]->connect_byte_output(
		this->components_[4]->release_byte_output(0));
      // Components 7:
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[2])->release_byte_output(0),
			(this->components_[3])->release_output(1)));
      this->components_[7]->connect_byte_output(
		this->components_[4]->release_byte_output(0));
      // Components 8:
      this->components_.push_back(
		std::make_shared<ByteNot>(
			(this->components_[2])->release_byte_output(0)));
      // Components 9:
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[8])->release_byte_output(0),
			(this->components_[3])->release_output(3)));
      this->components_[9]->connect_byte_output(
		this->components_[4]->release_byte_output(0));
      // Components 10:
      this->components_.push_back(
		std::make_shared<ByteAdder>() );
      this->components_[10]->connect_byte_input(
		this->byte_cin_[1]->release_byte_output(0), 0);
      this->components_[10]->connect_byte_input(
		this->byte_cin_[2]->release_byte_output(0), 1);
      // Components 11:
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[10])->release_byte_output(0),
			(this->components_[3])->release_output(4)));
      this->components_[11]->connect_byte_output(
		this->components_[4]->release_byte_output(0));
      // Components 12:
      this->components_.push_back(
		std::make_shared<ByteNeg>(
			(this->byte_cin_[2])->release_byte_output(0)));
      this->components_.push_back(
		std::make_shared<ByteAdder>() );
      this->components_[13]->connect_byte_input(
		this->byte_cin_[1]->release_byte_output(0), 0);
      this->components_[13]->connect_byte_input(
		this->components_[12]->release_byte_output(0), 1);
      // Components 14:
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[13])->release_byte_output(0),
			(this->components_[3])->release_output(5)));
      this->components_[14]->connect_byte_output(
		this->components_[4]->release_byte_output(0));


      this->byte_cout_[0]->connect_byte_input(
			this->components_[4]->release_byte_output(0), 0);
    }
};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

ArithmeticEngine circuit = ArithmeticEngine();
std::vector<std::uint8_t> input{1, 17, 178};
circuit.tick(input);
input[0] = 4;
input[1] = 54;
input[2] = 33;
circuit.tick(input);
input[0] = 5;
input[1] = 179;
input[2] = 155;
circuit.tick(input);
input[0] = 0;
input[1] = 34;
input[2] = 41;
circuit.tick(input);
input[1] = 226;
input[2] = 4;
circuit.tick(input);
input[0] = 5;
input[1] = 132;
input[2] = 180;
circuit.tick(input);
input[0] = 0;
input[1] = 133;
input[2] = 171;
circuit.tick(input);
input[0] = 5;
input[1] = 84;
input[2] = 151;
circuit.tick(input);
input[0] = 0;
input[1] = 28;
input[2] = 111;
circuit.tick(input);
input[0] = 2;
input[1] = 84;
input[2] = 37;
circuit.tick(input);
input[1] = 4;
input[2] = 77;
circuit.tick(input);
input[0] = 5;
input[1] = 11;
input[2] = 251;
circuit.tick(input);
input[0] = 5;
input[1] = 54;
input[2] = 9;
circuit.tick(input);
input[0] = 1;
input[1] = 142;
input[2] = 236;
circuit.tick(input);
input[1] = 73;
input[2] = 157;
circuit.tick(input);

std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b239 b87 b24 b43 b230 b208 b175 b189 ") +
					"b127 b138 b178 b16 b45 b115 b246 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
