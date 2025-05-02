// 20b - Little Box
#include "circuit.hpp"
#include "onebitdecoder.hpp"
#include "and.hpp"
#include "toggledbit.hpp"
#include "word_memory.hpp"
#include <sstream>
#include <iostream>

using namespace Virtual;

class LittleBox : public Circuit<4,1,0,0,1,0> {
  public:
    LittleBox() {
      this->init();
      this->components_.push_back(
		std::make_shared<OneBitDecoder>(
			(this->bit_cin_[2])->release_output(0)));
      this->components_.push_back(
		std::make_shared<OneBitDecoder>(
			(this->bit_cin_[3])->release_output(0)));
      // And gates are components 2 through 5
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[0])->release_output(0),
			(this->components_[1])->release_output(0)));
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[0])->release_output(1),
			(this->components_[1])->release_output(0)));
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[0])->release_output(0),
			(this->components_[1])->release_output(1)));
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[0])->release_output(1),
			(this->components_[1])->release_output(1)));
      // Load toggles
      // Components 6 - 9
      this->components_.push_back(
		std::make_shared<ToggledBit>(
			(this->bit_cin_[0])->release_output(0),
			(this->components_[2])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledBit>(
			(this->bit_cin_[0])->release_output(0),
			(this->components_[3])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledBit>(
			(this->bit_cin_[0])->release_output(0),
			(this->components_[4])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledBit>(
			(this->bit_cin_[0])->release_output(0),
			(this->components_[5])->release_output(0)));
      // Save toggles
      // Components 10 - 13
      this->components_.push_back(
		std::make_shared<ToggledBit>(
			(this->bit_cin_[1])->release_output(0),
			(this->components_[2])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledBit>(
			(this->bit_cin_[1])->release_output(0),
			(this->components_[3])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledBit>(
			(this->bit_cin_[1])->release_output(0),
			(this->components_[4])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledBit>(
			(this->bit_cin_[1])->release_output(0),
			(this->components_[5])->release_output(0)));
      // Memory registers
      // Component 14:
      this->components_.push_back(
		std::make_shared<ByteMemory>(
			(this->components_[6])->release_output(0),
			(this->components_[10])->release_output(0),
			(this->byte_cin_[0])->release_byte_output(0)));
      //this->memory_components_.push_back(
	//	this->components_[14] );
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[6])->release_output(0),
			(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[14])->release_byte_output(0),
			(this->components_[15])->release_output(0)));
      // Component 17:
      this->components_.push_back(
		std::make_shared<ByteMemory>(
			(this->components_[7])->release_output(0),
			(this->components_[11])->release_output(0),
			(this->byte_cin_[0])->release_byte_output(0)));
      //this->memory_components_.push_back(
	//	this->components_[17] );
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[7])->release_output(0),
			(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[17])->release_byte_output(0),
			(this->components_[18])->release_output(0)));
      this->components_[19]->connect_byte_output(
		this->components_[16]->release_byte_output(0));
      // Component 20:
      this->components_.push_back(
		std::make_shared<ByteMemory>(
			(this->components_[8])->release_output(0),
			(this->components_[12])->release_output(0),
			(this->byte_cin_[0])->release_byte_output(0)));
      //this->memory_components_.push_back(
	//	this->components_[20] );
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[8])->release_output(0),
			(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[20])->release_byte_output(0),
			(this->components_[21])->release_output(0)));
      this->components_[22]->connect_byte_output(
		this->components_[16]->release_byte_output(0));
      // Component 23:
      this->components_.push_back(
		std::make_shared<ByteMemory>(
			(this->components_[9])->release_output(0),
			(this->components_[13])->release_output(0),
			(this->byte_cin_[0])->release_byte_output(0)));
      //this->memory_components_.push_back(
	//	this->components_[23] );
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[9])->release_output(0),
			(this->bit_cin_[0])->release_output(0)));
      this->components_.push_back(
		std::make_shared<ToggledByte>(
			(this->components_[23])->release_byte_output(0),
			(this->components_[24])->release_output(0)));
      this->components_[25]->connect_byte_output(
		this->components_[16]->release_byte_output(0));
      this->byte_cout_[0]->connect_byte_input(
		this->components_[16]->release_byte_output(0), 0);
    }

};
      

int main() {

std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

LittleBox circuit = LittleBox();
std::vector<bool> inputb{false,true,false,false};
std::vector<std::uint8_t> input{245};
circuit.tick(inputb, input);
inputb[0] = true;
inputb[1] = false;
circuit.tick(inputb, input);
inputb[0] = false;
inputb[1] = true;
inputb[2] = true;
input[0] = 42;
circuit.tick(inputb, input);
inputb[0] = true;
inputb[1] = false;
circuit.tick(inputb, input);
inputb[0] = false;
inputb[1] = true;
inputb[2] = false;
inputb[3] = true;
input[0] = 134;
circuit.tick(inputb, input);
inputb[0] = true;
inputb[1] = false;
input[0] = 152;
circuit.tick(inputb, input);
inputb[0] = false;
inputb[1] = true;
inputb[2] = true;
input[0] = 54;
circuit.tick(inputb, input);
inputb[0] = true;
inputb[1] = false;
input[0] = 1;
circuit.tick(inputb, input);
inputb[0] = false;
inputb[1] = true;
input[0] = 252;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 35;
circuit.tick(inputb, input);
inputb[3] = false;
input[0] = 74;
circuit.tick(inputb, input);
inputb[0] = false;
inputb[3] = true;
input[0] = 135;
circuit.tick(inputb, input);
inputb[0] = true;
input[0] = 47;
circuit.tick(inputb, input);
inputb[2] = false;
input[0] = 38;
circuit.tick(inputb, input);
inputb[2] = true;
input[0] = 157;
circuit.tick(inputb, input);
inputb[2] = false;
inputb[3] = false;
input[0] = 153;
circuit.tick(inputb, input);
inputb[1] = false;
inputb[2] = true;
inputb[3] = true;
input[0] = 144;
circuit.tick(inputb, input);
inputb[1] = true;
inputb[3] = false;
input[0] = 111;
circuit.tick(inputb, input);


std::cout.rdbuf(old);

std::string capturedOutput = buffer.str();
std::string expectedOutput = std::string("b0 b245 b245 b42 b42 b134 b134 ") +
		"b54 b54 b252 b42 b42 b135 b134 b47 b245 b157 b74 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
