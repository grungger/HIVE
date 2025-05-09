/*****************************************
 * @file arithmetic_logic_unit.hpp
 * 
 * @brief Implementation of ArithmeticLogicUnit which decodes 
 *   the opcode of the Turing Complete architecture and computes
 *   the logic gate determined by the opcode.
 *****************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "threebitdecoder.hpp"
#include "not.hpp"
#include "word_not.hpp"
#include "word_or.hpp"
#include "word_neg.hpp"
#include "word_adder.hpp"
#include "toggledword.hpp"

// Header Guards:
#ifndef ARITHMETICLOGICUNIT_H
#define ARITHMETICLOGICUNIT_H

namespace Virtual{

/**
 * @brief ArithmeticLogicUnit decodes an 8bit instruction set and 
 *   applies the corresponding arithmetic operation.
 */
class ArithmeticLogicUnit : public byteMicroCircuit<0,3,0,1,17> {
  public:
    /**
     * @brief Constructor sets up the decoder.
     */
    ArithmeticLogicUnit(ptr8_t instruction=ground8, 
		    	ptr8_t inputA=ground8,
			ptr8_t inputB=ground8);

    /**
     * @brief rewire_input resets internal circuitry in case inputs changed.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
