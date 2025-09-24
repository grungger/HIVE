/****************************************************************
 * This circuit builds a fully Turing complete CPU with 
 * a Program input, 1kB of RAM and a 32x32pixel Display output,
 * with the name HIVEmind.
 */

#include "circuit.hpp"
#include "program.hpp"
#include "counter.hpp"
#include "SourceDestDecoder.hpp"
#include "register_plus.hpp"
#include "ArithmeticLogicUnit.hpp"
#include "ConditionalUnit.hpp"
#include "RAM.hpp"
#include "display.hpp"

#include "word_maker.hpp"
#include "word_splitter.hpp"
#include "word_mux.hpp"
#include "or.hpp"
#include "not.hpp"
#include "and3.hpp"
#include "and.hpp"

#include "wire.hpp"

#include <iostream>

#ifndef HIVEMIND_H
#define HIVEMIND_H

namespace Virtual{

/**
 * Opcodes:
 * 0 Immediate (byte), 1 Immediate (half word), 2 Compute, 3 Copy, 4 Condition,
 * 7 Flush Display, +32 Destinaton is RAM, +64 Source is RAM, +128 Immediate (word).
 * Conditional operators:
 * 0 EQ, 1 NE, 2 GE, 3 G, 4 LE, 5 L, 6 GES, 7 GS, 8 LES, 9 LS, 10 AL, 11 N
 * Arithmetic operators:
 * 0 NOT, 1 AND, 2 NAND, 3 OR, 4 NOR, 5 XOR, 6 BIC, 7 ADD, 8 ADC, 9 SUB, 10 SBC,
 * 11 RSB, 12 RSC, 13 ASR, 14 LSR, 15 LSL
 *
 * HIVEmind
 */
class HIVEmind : public Circuit<0,0,0,0,0,0> {
  public:
    HIVEmind() {
      this->init();
      // C0 Counter (uncon)
      this->components_.push_back(
		      std::make_shared<Counter>());
      this->memory_components_.push_back(this->components_[0]);
      // C1 Program
      this->components_.push_back(
		      std::make_shared<Program>(
			      (this->components_[0])->release_word_output(0)));
      // C2 SourceDestDecoderHIVE
      this->components_.push_back(
		      std::make_shared<SourceDestDecoderHIVE>(
			      (this->components_[1])->release_word_output(0)));
      // C3 WordByter (Full opcode to sub-Bytes)
      this->components_.push_back(
		      std::make_shared<WordByter>(
			      (this->components_[1])->release_word_output(0)));
      // C4 WordMakerByte (value of Immediate Byte 0)
      this->components_.push_back(
		      std::make_shared<WordMakerByte>(
			      (this->components_[3])->release_byte_output(2)));
      // C5 WordMakerByte (value of Immediate half word 1)
      this->components_.push_back(
		      std::make_shared<WordMakerByte>(
			      (this->components_[3])->release_byte_output(1),
			      (this->components_[3])->release_byte_output(2)));
      // C6 ByteSplitter (split mode Byte)
      this->components_.push_back(
		      std::make_shared<ByteSplitter>(
			      (this->components_[3])->release_byte_output(3)));
      // C7 ByteMaker (recombine mode Byte without MSB)
      this->components_.push_back(
		      std::make_shared<ByteMaker>(
			      (this->components_[6])->release_output(0),
			      (this->components_[6])->release_output(1),
			      (this->components_[6])->release_output(2),
			      (this->components_[6])->release_output(3),
			      (this->components_[6])->release_output(4),
			      (this->components_[6])->release_output(5),
			      (this->components_[6])->release_output(6)));
      // C8 WordMakerByte (Immediate +128 value)
      this->components_.push_back(
		      std::make_shared<WordMakerByte>(
			      (this->components_[3])->release_byte_output(0),
			      (this->components_[3])->release_byte_output(1),
			      (this->components_[3])->release_byte_output(2),
			      (this->components_[7])->release_byte_output(0)));
      // C9 WordMUX either mode 0 or mode 1
      this->components_.push_back(
		      std::make_shared<WordMUX>(
			      (this->components_[2])->release_output(1),
			      (this->components_[4])->release_word_output(0),
			      (this->components_[5])->release_word_output(0)));
      // C10 Or mode 0 or mode 1
      this->components_.push_back(
		      std::make_shared<Or>(
			      (this->components_[2])->release_output(0),
			      (this->components_[2])->release_output(1)));
      // C11 WordMUX either mode 0/1 or +128
      this->components_.push_back(
		      std::make_shared<WordMUX>(
			      (this->components_[2])->release_output(8),
			      (this->components_[9])->release_word_output(0),
			      (this->components_[8])->release_word_output(0)));
      // C12 Or -> any Immediate mode
      this->components_.push_back(
		      std::make_shared<Or>(
			      (this->components_[10])->release_output(0),
			      (this->components_[2])->release_output(8)));
      // C13 ByteSplitter Aaddress split
      this->components_.push_back(
		      std::make_shared<ByteSplitter>(
			      (this->components_[3])->release_byte_output(2)));
      // C14 WordMaker Aaddress without MSB -> immediate address value
      this->components_.push_back(
		      std::make_shared<WordMaker>(
			      (this->components_[13])->release_output(0),
			      (this->components_[13])->release_output(1),
			      (this->components_[13])->release_output(2),
			      (this->components_[13])->release_output(3),
			      (this->components_[13])->release_output(4),
			      (this->components_[13])->release_output(5),
			      (this->components_[13])->release_output(6)));
      // C15 ToggledWord A IMMEDIATE VALUE -> GLOBAL A OUTPUT
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[14])->release_word_output(0),
			      (this->components_[2])->release_output(26)));
      // C16 ByteSplitter Baddress split
      this->components_.push_back(
		      std::make_shared<ByteSplitter>(
			      (this->components_[3])->release_byte_output(1)));
      // C17 WordMaker Baddress without MSB -> immediate address value
      this->components_.push_back(
		      std::make_shared<WordMaker>(
			      (this->components_[16])->release_output(0),
			      (this->components_[16])->release_output(1),
			      (this->components_[16])->release_output(2),
			      (this->components_[16])->release_output(3),
			      (this->components_[16])->release_output(4),
			      (this->components_[16])->release_output(5),
			      (this->components_[16])->release_output(6)));
      // C18 ToggledWord B IMMEDIATE VALUE -> GLOBAL B OUTPUT
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[17])->release_word_output(0),
			      (this->components_[2])->release_output(45)));
      // C19 Not Source is not Immediate
      this->components_.push_back(
		      std::make_shared<Not>(
			      (this->components_[2])->release_output(26)));
      // C20 Not Dest is not Immediate
      this->components_.push_back(
		      std::make_shared<Not>(
			      (this->components_[2])->release_output(45)));
      // C21 Or Full Immediate or Dest is RAM (+32)
      this->components_.push_back(
		      std::make_shared<Or>(
			      (this->components_[2])->release_output(8),
			      (this->components_[2])->release_output(6)));
      // C22 Not = ~(M+32 | M+128)
      this->components_.push_back(
		      std::make_shared<Not>(
			      (this->components_[21])->release_output(0)));
      // C23 Or Full Immediate or Source is RAM (+64)
      this->components_.push_back(
		      std::make_shared<Or>(
			      (this->components_[2])->release_output(8),
			      (this->components_[2])->release_output(7)));
      // C24 Not = ~(M+64 | M+128)
      this->components_.push_back(
		      std::make_shared<Not>(
			      (this->components_[23])->release_output(0)));
      // C25 And3 ~(D+128) & M3 & ~(M+32 | M+128)
      this->components_.push_back(
		      std::make_shared<And3>(
			      (this->components_[20])->release_output(0),
			      (this->components_[2])->release_output(3),
			      (this->components_[22])->release_output(0)));
      // C26 And D0 & C25
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[2])->release_output(27),
			      (this->components_[25])->release_output(0)));
      // C27 Or -> Reg0 Save
      this->components_.push_back(
		      std::make_shared<Or>(
			      (this->components_[26])->release_output(0),
			      (this->components_[12])->release_output(0)));
      // C28 And D1 & C25 -> Reg1 Save
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[2])->release_output(28),
			      (this->components_[25])->release_output(0)));
      // C29 And D2 & C25 -> Reg2 Save
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[2])->release_output(29),
			      (this->components_[25])->release_output(0)));
      // C30 And D3 & C25
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[2])->release_output(30),
			      (this->components_[25])->release_output(0)));
      // C31 Or C30 or M2 -> Reg3 Save
      this->components_.push_back(
		      std::make_shared<Or>(
			      (this->components_[30])->release_output(0),
			      (this->components_[2])->release_output(2)));
      // C32 - C43 And Di & C25 -> Reg4-15 Save
      for (int i=4; i<16; i++) {
	      this->components_.push_back(
			      std::make_shared<And>(
				      (this->components_[2])->release_output(27+i),
				      (this->components_[25])->release_output(0)));
      }
      // TODO BIG ISSUE WRONG C47 IS WRONG COUNT OF C43
      // QUICK FIX ADD EMPTY WIRES
      for (int i=0; i<4;i++) { this->components_.push_back(
		      std::make_shared<Wire>()); }
      // TODO FIX
      // std::cout << "Now we expect 48 -> " << (this->components_).size() << std::endl;
      // C48 Or = M2 or M4 (no copy)
      this->components_.push_back(
		      std::make_shared<Or>(
			      (this->components_[2])->release_output(2),
			      (this->components_[2])->release_output(4)));
      // C49 Or = M2 or M4 or M3
      this->components_.push_back(
		      std::make_shared<Or>(
			      (this->components_[48])->release_output(0),
			      (this->components_[2])->release_output(3)));
      // C50 And3 C19 and C49 and C24
      this->components_.push_back(
		      std::make_shared<And3>(
			      (this->components_[19])->release_output(0),
			      (this->components_[24])->release_output(0),
			      (this->components_[49])->release_output(0)));
      // C51 And3 C20 and C48 and C22
      this->components_.push_back(
		      std::make_shared<And3>(
			      (this->components_[20])->release_output(0),
			      (this->components_[22])->release_output(0),
			      (this->components_[48])->release_output(0)));
      // C52-99 (Si and C50), (Di and C51), ->Regi load
      for (int i=0;i<16;i++) {
	      // C52+*3i And Si and C50
	      this->components_.push_back(
			      std::make_shared<And>(
				      (this->components_[2])->release_output(9+i),
				      (this->components_[50])->release_output(0)));
	      // C53+3*i And Di and C51
	      this->components_.push_back(
			      std::make_shared<And>(
				      (this->components_[2])->release_output(27+i),
				      (this->components_[51])->release_output(0)));
	      // C54+3*i -> Regi load
	      this->components_.push_back(
			      std::make_shared<Or>(
				      (this->components_[52+3*i])->release_output(0),
				      (this->components_[53+3*i])->release_output(0)));
      }
      // C100 Not Full Immediate
      this->components_.push_back(
		      std::make_shared<Not>(
			      (this->components_[2])->release_output(8)));
      // C101 And (any M2,3,4 And not Full immediate)
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[100])->release_output(0),
			      (this->components_[49])->release_output(0)));
      // C102 And -> RAM->Aload
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[101])->release_output(0),
			      (this->components_[2])->release_output(7)));
      // C103 And -> RAM->Btog
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[101])->release_output(0),
			      (this->components_[2])->release_output(6)));
      // C104 And (M2 and not Immediate) -> ALU->toggle
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[2])->release_output(2),
			      (this->components_[100])->release_output(0)));
      // C105 ALU
      this->components_.push_back(
		      std::make_shared<ALU_HIVE>(
			      (this->components_[104])->release_output(0),
			      (this->components_[3])->release_byte_output(0)));
        // this is where carryRegister should be connected...
      (this->components_[105])->connect_word_input(
		      (this->components_[15])->release_word_output(0),0);
      (this->components_[105])->connect_word_input(
		      (this->components_[18])->release_word_output(0),1);

      // C106 WordMUX either generalOutA or ALU output -> Reg3 val
      this->components_.push_back(
		      std::make_shared<WordMUX>(
			      (this->components_[104])->release_output(0),
			      (this->components_[15])->release_word_output(0),
			      (this->components_[105])->release_word_output(0)));
      // CNEW107 WordMUX either generalOutA or Immediate -> Reg0 val
      this->components_.push_back(
		      std::make_shared<WordMUX>(
			      (this->components_[12])->release_output(0),
			      (this->components_[15])->release_word_output(0),
			      (this->components_[11])->release_word_output(0)));
      // C108(107 Reg0
      this->components_.push_back(
		      std::make_shared<RegisterMax>(
			      (this->components_[54])->release_output(0),
			      (this->components_[27])->release_output(0),
			      (this->components_[107])->release_word_output(0))); //old: 107 <-> 15
      this->memory_components_.push_back(this->components_[107]);
      // C109(108 ToggledWord Reg0 output to A
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[108])->release_word_output(0), // old: 108 <-> 107
			      (this->components_[52])->release_output(0)));
      (this->components_[109])->connect_word_output( // old: 109 <-> 108
		      (this->components_[15])->release_word_output(0));
      this->memory_components_.push_back(this->components_[109]); // old 109 <-> 108
      // C110(109 ToggledWord Reg0 output to B
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[108])->release_word_output(0), // old 108 <-> 107
			      (this->components_[53])->release_output(0)));
      this->memory_components_.push_back(this->components_[110]);
      (this->components_[110])->connect_word_output(
		      (this->components_[18])->release_word_output(0));
      // C111(110 Reg1
      this->components_.push_back(
		      std::make_shared<RegisterMax>(
			      (this->components_[57])->release_output(0),
			      (this->components_[28])->release_output(0),
			      (this->components_[15])->release_word_output(0)));
      this->memory_components_.push_back(this->components_[111]);

      // C112(111 ToggledWord Reg1 output to A
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[111])->release_word_output(0),
			      (this->components_[55])->release_output(0)));
      (this->components_[112])->connect_word_output(
		      (this->components_[15])->release_word_output(0));
      this->memory_components_.push_back(this->components_[112]);

      // C113(112 ToggledWord Reg1 output to B
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[111])->release_word_output(0),
			      (this->components_[56])->release_output(0)));
      (this->components_[113])->connect_word_output(
		      (this->components_[18])->release_word_output(0));
      this->memory_components_.push_back(this->components_[113]);

      // C114(113 Reg2
      this->components_.push_back(
		      std::make_shared<RegisterMax>(
			      (this->components_[60])->release_output(0),
			      (this->components_[29])->release_output(0),
			      (this->components_[15])->release_word_output(0)));
      this->memory_components_.push_back(this->components_[114]);

      // C115(114 ToggledWord Reg2 output to A
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[114])->release_word_output(0),
			      (this->components_[58])->release_output(0)));
      (this->components_[115])->connect_word_output(
		      (this->components_[15])->release_word_output(0));
      this->memory_components_.push_back(this->components_[115]);

      // C116(115 ToggledWord Reg2 output to B
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[114])->release_word_output(0),
			      (this->components_[59])->release_output(0)));
      (this->components_[116])->connect_word_output(
		      (this->components_[18])->release_word_output(0));
      this->memory_components_.push_back(this->components_[116]);

      // C117(116 Reg3
      this->components_.push_back(
		      std::make_shared<RegisterMax>(
			      (this->components_[63])->release_output(0),
			      (this->components_[31])->release_output(0),
			      (this->components_[106])->release_word_output(0)));
      this->memory_components_.push_back(this->components_[117]);

      // C118(117 ToggledWord Reg3 output to A
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[117])->release_word_output(0),
			      (this->components_[61])->release_output(0)));
      (this->components_[118])->connect_word_output(
		      (this->components_[15])->release_word_output(0));
      this->memory_components_.push_back(this->components_[118]);

      // C119(118 ToggledWord Reg3 output to B
      this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[117])->release_word_output(0),
			      (this->components_[62])->release_output(0)));
      (this->components_[119])->connect_word_output(
		      (this->components_[18])->release_word_output(0));
      this->memory_components_.push_back(this->components_[119]);

      for (int i=4; i<16; i++) {
      	// C120(119+3*(i-4) Regi
      	this->components_.push_back(
		      std::make_shared<RegisterMax>(
			      (this->components_[66+3*(i-4)])->release_output(0),
			      (this->components_[32+(i-4)])->release_output(0),
			      (this->components_[15])->release_word_output(0)));
        this->memory_components_.push_back(this->components_[120+3*(i-4)]);

      	// C121(120+3*(i-4) ToggledWord Regi output to A
      	this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[120+3*(i-4)])->release_word_output(0),
			      (this->components_[64+3*(i-4)])->release_output(0)));
	(this->components_[121+3*(i-4)])->connect_word_output(
			(this->components_[15])->release_word_output(0));
        this->memory_components_.push_back(this->components_[121+3*(i-4)]);

      	// C122(121+3*(i-4) ToggledWord Regi output to B
      	this->components_.push_back(
		      std::make_shared<ToggledWord>(
			      (this->components_[120+3*(i-4)])->release_word_output(0),
			      (this->components_[65+3*(i-4)])->release_output(0)));
	(this->components_[122+3*(i-4)])->connect_word_output(
			(this->components_[18])->release_word_output(0));
        this->memory_components_.push_back(this->components_[122+3*(i-4)]);

	}
      // C156(155 RAM
      this->components_.push_back(
		      std::make_shared<RAM>(
			      (this->components_[2])->release_output(3),
			      (this->components_[102])->release_output(0),
			      (this->components_[103])->release_output(0),
			      (this->components_[3])->release_byte_output(2),
			      (this->components_[3])->release_byte_output(1),
			      (this->components_[15])->release_word_output(0)));
      (this->components_[156])->connect_word_output_i(
		      (this->components_[15])->release_word_output(0), false);
      (this->components_[156])->connect_word_output_i(
		      (this->components_[18])->release_word_output(0), true);
      this->memory_components_.push_back(this->components_[156]);

      // C157(156 And (M4 and Not Full Immediate) ->CondUnit toggle
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[2])->release_output(4),
			      (this->components_[100])->release_output(0)));
      // C158(157 ConditionalUnit
      this->components_.push_back(
		      std::make_shared<ConditionalUnitHIVE>(
			      (this->components_[157])->release_output(0),
			      (this->components_[3])->release_byte_output(0),
			      (this->components_[15])->release_word_output(0),
			      (this->components_[18])->release_word_output(0)));
      // finally connecting Counter inputs
      (this->components_[0])->connect_input(
		      (this->components_[158])->release_output(0),0);
      (this->components_[0])->connect_word_input(
		      (this->components_[108])->release_word_output(1),0);
      // C159(158 And (D17 and C25[~(D+128) & M3 & ~(M+32 | M+128)])
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[25])->release_output(0),
			      (this->components_[2])->release_output(44)));
      // C160(159 And (M7 and notFullImmediate)
      this->components_.push_back(
		      std::make_shared<And>(
			      (this->components_[2])->release_output(5),
			      (this->components_[100])->release_output(0)));
      // C161(160 Display
      this->components_.push_back(
		      std::make_shared<Display>(
		      (this->components_[159])->release_output(0),
			      (this->components_[160])->release_output(0),
			      (this->components_[15])->release_word_output(0),
			      3.0));
    }

    void add_lines(const std::vector<std::uint32_t>& container) {
      this->components_[1]->add_lines(container);
    }

    void tick() {
      (*memory_components_.begin())->memory_release();
      for (auto it=components_.begin()+1;it!=components_.begin()+105;it++){
	      (*it)->compute_output();
	    }
      for (auto it=memory_components_.begin()+1; it!=memory_components_.end(); it++) {
        (*it)->memory_release();
	//(*it)->print_in();
	//(*it)->print_out();
	//std::cout << std::endl;
      }
      int counting = 0;
      for (auto it=components_.begin(); it!=components_.end(); it++) {
	//std::cout << "C" << counting++;
        (*it)->compute_output();
	//std::cout << "in";
	//(*it)->print_in();
	//std::cout << "out";
	//(*it)->print_out();
	//std::cout << std::endl;
      }
      components_[0]->memory_receive();
      // std::cout << "Display ";
      // this->components_[160]->printMemory();
      // std::cout << std::endl;
    }
};


}

#endif
