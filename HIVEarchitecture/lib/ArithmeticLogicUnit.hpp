/*****************************************
 * @file ArithmeticLogicUnit.hpp
 * 
 * @brief Implementation of ALU_HIVE which decodes 
 *   the opcode of the HIVE architecture and computes
 *   the logic gate determined by the opcode.
 *****************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "fourbitdecoder.hpp"
#include "word_not.hpp"
#include "toggledword.hpp"
#include "word_and.hpp"
#include "word_nand.hpp"
#include "word_or.hpp"
#include "word_nor.hpp"
#include "word_xor.hpp"
#include "word_adder.hpp"
#include "word_neg.hpp"
#include "xor.hpp"
#include "and.hpp"
#include "fivebitdecoder.hpp"
#include "word_maker.hpp"
#include "toggledbit.hpp"

// Header Guards:
#ifndef ALU_HIVE_H
#define ALU_HIVE_H

namespace Virtual{

/**
 * @brief ALU_HIVE decodes a 32bit instruction set and 
 *   applies the corresponding arithmetic operation.
 * 
 * ALU_HIVE implements the following operations: 
 *   Not, And, Nand, Or, Nor, Xor, BIC, Add, AddC, Sub, SubC,
 *   RevSub, RevSubC, ArithShiftR, LogShiftR, LogShiftL, (ROR)
 * Unary operations are computed on inputA.
 * The output byte corresponds to the carry byte 
 * with bit 1 for ADC, bit 1 for SBC & RSC borrow, bit 2 for SBC & RSC overflow.
 */
class ALU_HIVE : public wordMicroCircuit<1,2,2,0,1,1,243> {
  public:
    /**
     * @brief Constructor sets up the decoder.
     * @param toggle turns on or off the final output.
     * @param operation encodes which of the ALU operations to carry out (0-15 are in use).
     * @param carryRegister a copy of the carries from a previous computation -> needed in ADC etc.
     * @param inputA first operand.
     * @param inputB second operand.
     */
    ALU_HIVE(	ptr_t toggle=ground,
		ptr8_t operation=ground8,
	        ptr8_t carryRegister=ground8,	
		ptr32_t inputA=ground32,
		ptr32_t inputB=ground32 );

    /**
     * @brief rewire_input resets internal circuitry in case inputs changed.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
