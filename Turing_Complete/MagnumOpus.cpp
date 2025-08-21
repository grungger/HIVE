// Magnum Opus
#include "circuit.hpp"
#include "program.hpp"
#include "source_dest_decoder.hpp"
#include "or.hpp"
#include "and.hpp"
#include "not.hpp"
#include "word_mux.hpp"
#include "register_plus.hpp"
#include "arithmetic_logic_unit.hpp"
#include "conditional_unit.hpp"
#include "counter.hpp"
#include "toggledword.hpp"

#include <sstream>
#include <iostream>

using namespace Virtual;

/**
 * Bits 1 2 4 8 16 32 64 128
 * Bits 64 128 determine the mode:
 *   0 0 = immediate
 *   1 0 = calculate
 *   0 1 = copy
 *   1 1 = condition
 * In copy mode involving two registers the bits 1 2 4 are the destination and 
 * 8 16 32 are the source registers.
 * calculate mode uses bits 1 2 4 as the instruction computed on Reg1 and Reg2 
 * with the result saved to Reg3
 * condition mode uses the bits 1 2 4 as the instruction and if the condition 
 * is fulfilled by Reg3 the Counter will be overwritten with Reg0
 */
class MagnumOpus : public Circuit<0,1,0,0,1,0> {
  private:
    std::vector<std::uint8_t> inputs;
  public:
    MagnumOpus() {
      this->init();
      // C0 Counter (uncon)
      this->components_.push_back(
		std::make_shared<ByteCounter>());
      // necessary memory release of counter?
      this->memory_components_.push_back(this->components_[0]);
      // C1 Program
      this->components_.push_back(
		std::make_shared<ByteProgram>(
			(this->components_[0])->release_byte_output(0)));
      // C2 SourceDestDecoder
      this->components_.push_back(
		std::make_shared<SourceDestDecoder>(
			(this->components_[1])->release_byte_output(0)));
      // C3 Or (condition mode S0)
      this->components_.push_back(
	      	std::make_shared<Or>(
			(this->components_[2])->release_output(8),
			(this->components_[2])->release_output(19)));
      // C4 Or (Immediate D0)
      this->components_.push_back(
	        std::make_shared<Or>(
			(this->components_[2])->release_output(0),
			(this->components_[2])->release_output(16)));
      // C5 Not Compute
      this->components_.push_back(
	        std::make_shared<Not>(
			(this->components_[2])->release_output(17)));
      // C6 And (C4Or C5Not) -> save toggle Reg0
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[4])->release_output(0),
			(this->components_[5])->release_output(0)));
      // C7 And (D1 Copy) -> save toggle Reg1
      this->components_.push_back(
		std::make_shared<And>(
			(this->components_[2])->release_output(1),
			(this->components_[2])->release_output(18)));
      // C8 And (D2 Copy) -> save toggled Reg2
      this->components_.push_back(
		 std::make_shared<And>(
			 (this->components_[2])->release_output(2),
			 (this->components_[2])->release_output(18)));
      // C9 And (D3 Copy)
      this->components_.push_back(
		 std::make_shared<And>(
			 (this->components_[2])->release_output(3),
			 (this->components_[2])->release_output(18)));
      // C10 Or (C9And Calculate) -> save toggled Reg3
      this->components_.push_back(
		 std::make_shared<Or>(
			 (this->components_[9])->release_output(0),
			 (this->components_[2])->release_output(17)));
      // C11 And (D4 Copy) -> save toggled Reg4
      this->components_.push_back(
		 std::make_shared<And>(
			 (this->components_[2])->release_output(4),
			 (this->components_[2])->release_output(18)));
      // C12 And (D5 Copy) -> save toggled Reg5
      this->components_.push_back(
		 std::make_shared<And>(
			 (this->components_[2])->release_output(5),
			 (this->components_[2])->release_output(18)));
      // C13 And (D6 Copy) -> save toggled Output
      this->components_.push_back(
		 std::make_shared<And>(
			 (this->components_[2])->release_output(6),
			 (this->components_[2])->release_output(18)));
      // C14 ByteMUX (immediate uncon(global out) Program) -> save value Reg0
      this->components_.push_back(
		 std::make_shared<ByteMUX>());
      this->components_[14]->connect_input(
			 (this->components_[2])->release_output(16), 0);
      this->components_[14]->connect_byte_input(
		         (this->components_[1])->release_byte_output(0), 1);
      // C15 ByteMUX (calculate uncon(global out) uncon(ALU)) -> save value Reg3
      this->components_.push_back(
		  std::make_shared<ByteMUX>());
      this->components_[15]->connect_input(
		         (this->components_[2])->release_output(17), 0);
      // C16 RegisterPlus (Reg0)
      this->components_.push_back(
		  std::make_shared<RegisterPlus>(
			 (this->components_[3])->release_output(0),
			 (this->components_[6])->release_output(0),
			 (this->components_[14])->release_byte_output(0)));
      this->memory_components_.push_back(this->components_[16]);
      //// C16 toggled output is now the universal output->connect all necessary:
      this->components_[14]->connect_byte_input(
		      (this->components_[16])->release_byte_output(0), 0);
      this->components_[15]->connect_byte_input(
		      (this->components_[16])->release_byte_output(0), 0);
      // C17 RegisterPlus (Reg1)
      this->components_.push_back(
		  std::make_shared<RegisterPlus>(
			  (this->components_[2])->release_output(9),
			  (this->components_[7])->release_output(0),
			  (this->components_[16])->release_byte_output(0)));
      this->components_[17]->connect_byte_output(
		      (this->components_[16])->release_byte_output(0));
      this->memory_components_.push_back(this->components_[17]);
      // C18 RegisterPlus (Reg2)
      this->components_.push_back(
		      std::make_shared<RegisterPlus>(
			      (this->components_[2])->release_output(10),
			      (this->components_[8])->release_output(0),
			      (this->components_[16])->release_byte_output(0)));
      this->components_[18]->connect_byte_output(
		      this->components_[16]->release_byte_output(0));
      this->memory_components_.push_back(this->components_[18]);
      // C19 RegisterPlus (Reg3)
      this->components_.push_back(
		      std::make_shared<RegisterPlus>(
			      (this->components_[2])->release_output(11),
			      (this->components_[10])->release_output(0),
			      (this->components_[15])->release_byte_output(0)));
      this->components_[19]->connect_byte_output(
		      this->components_[16]->release_byte_output(0));
      this->memory_components_.push_back(this->components_[19]);
      // C20 RegisterPlus (Reg4)
      this->components_.push_back(
		      std::make_shared<RegisterPlus>(
			      (this->components_[2])->release_output(12),
			      (this->components_[11])->release_output(0),
			      (this->components_[16])->release_byte_output(0)));
      this->components_[20]->connect_byte_output(
		      this->components_[16]->release_byte_output(0));
      this->memory_components_.push_back(this->components_[20]);
      // C21 RegisterPlus (Reg5)
      this->components_.push_back(
		      std::make_shared<RegisterPlus>(
			      (this->components_[2])->release_output(13),
			      (this->components_[12])->release_output(0),
			      (this->components_[16])->release_byte_output(0)));
      this->components_[21]->connect_byte_output(
		      this->components_[16]->release_byte_output(0));
      this->memory_components_.push_back(this->components_[21]);
      // C22 ToggledByte for Output
      this->components_.push_back(
		      std::make_shared<ToggledByte>(
			      (this->components_[16])->release_byte_output(0),
			      (this->components_[13])->release_output(0), true));
      // C23 And (Copy S6)
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[2])->release_output(18),
			      (this->components_[2])->release_output(14)));
      // C24 ToggledByte for Input
      this->components_.push_back(
		      std::make_shared<ToggledByte>(
			      (this->byte_cin_[0])->release_byte_output(0),
			      (this->components_[23])->release_output(0)));
      this->components_[24]->connect_byte_output(
		      (this->components_[16])->release_byte_output(0));
      // C25 ConditionalUnit (Program Reg3)
      this->components_.push_back(
		      std::make_shared<ConditionalUnit>(
			      (this->components_[1])->release_byte_output(0),
			      (this->components_[19])->release_byte_output(1)));
      // C26 And (Conditional ConditionalUnit) -> Counter overwrite toggle
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[2])->release_output(19),
			      (this->components_[25])->release_output(0)));
      //// finally connecting Counter input
      this->components_[0]->connect_input(
		      this->components_[26]->release_output(0), 0);
      this->components_[0]->connect_byte_input(
		      this->components_[16]->release_byte_output(1),0);
      // C27 ArithmeticLogicUnit (Program Reg1 Reg2)
      this->components_.push_back(
		      std::make_shared<ArithmeticLogicUnit>(
			      (this->components_[1])->release_byte_output(0),
			      (this->components_[17])->release_byte_output(1),
			      (this->components_[18])->release_byte_output(1)));
      //// finally connecting ByteMux for Reg3
      this->components_[15]->connect_byte_input(
		      (this->components_[27])->release_byte_output(0), 1);

      this->byte_cout_[0]->connect_byte_input(
			this->components_[22]->release_byte_output(0), 0);
    }

    void add_lines(const std::vector<std::uint8_t>& container) {
      this->components_[1]->add_lines(container);
    }
    
    void set_input_vals(std::vector<std::uint8_t> vals) {
      this->inputs = vals;
    }
    void tick() {
      byte_cin_[0]->change_state(inputs[0]);
      int counting = 0;
      std::cout << "Mem release ";
      for (auto it=memory_components_.begin(); it!=memory_components_.end(); it++) {
        (*it)->memory_release();
	(*it)->print_in();
	(*it)->print_out();
	std::cout << std::endl;
      }
      // Run all components:
      // std::cout << "CompRun ";
      for (auto it=components_.begin(); it!=components_.end(); it++) {
	std::cout << "C" << counting++;
        (*it)->compute_output();
	std::cout << "in";
	(*it)->print_in();
	std::cout << "out";
	(*it)->print_out();
	std::cout << std::endl;
      }
      // Print memory:
      //std::cout << "Program";
      //components_[1]->print_out();
      //std::cout << " ";
      //int comp_index = 2;
      //std::cout << "C" << comp_index;
      //components_[comp_index]->print_out();
      std::cout << "Mem";
      for (auto it=memory_components_.begin(); it!=memory_components_.end(); it++) {
	std::cout << (*it)->gate_name;
        (*it)->print_out();
      }
      // Print outputs:
      std::cout << "Out";
      for (auto it=byte_cout_.begin(); it!=byte_cout_.end(); it++) {
        (*it)->compute_output();
      }
      std::cout << ' ';
    }

};
      

int main() {

//std::stringstream buffer;
//std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

MagnumOpus circuit = MagnumOpus();
std::vector<std::uint8_t> program{5, 130, 177, 68, 158};
std::vector<std::uint8_t> input{69};
circuit.add_lines(program);
circuit.set_input_vals(input);
circuit.tick();
circuit.tick();
circuit.tick();
circuit.tick();
circuit.tick();

//std::cout.rdbuf(old);

std::string capturedOutput = "bla"; //buffer.str();
std::string expectedOutput = std::string("b239 b87 b24 b43 b230 b208 b175 b189 ") +
					"b127 b138 b178 b16 b45 b115 b246 ";

if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}
}
