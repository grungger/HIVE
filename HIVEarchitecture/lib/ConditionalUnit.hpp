/*****************************************
 * @file ConditionalUnit.hpp
 * 
 * @brief Implementation of ConditionalUnitHIVE which decodes 
 *   the opcode of the HIVE architecture and computes
 *   the condition.
 *****************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "fourbitdecoder.hpp"
#include "toggledbit.hpp"
#include "word_neg.hpp"
#include "word_adder.hpp"
#include "not.hpp"
#include "word_not.hpp"
#include "xor.hpp"
#include "and.hpp"

// Header Guards:
#ifndef CONDITIONALUNITHIVE_H
#define CONDITIONALUNITHIVE_H

namespace Virtual{

/**
 * @brief ConditionalUnitHIVE decodes an 8bit instruction acting on two words and applies the condition.
 */
class ConditionalUnitHIVE : public wordMicroCircuit<1,1,2,1,0,0,34> {
  public:
    /**
     * @brief Constructor sets up the conditional unit.
     * @param toggle based on instruction opcode whether we are in Condition mode.
     * @param operation encodes the conditional operation to be executed on A and B.
     * @param inputA is input A.
     * @param inputB is input B.
     */
    ConditionalUnitHIVE(ptr_t toggle=ground, ptr8_t operation=ground8, ptr32_t inputA=ground32, ptr32_t inputB=ground32);

    /**
     * @brief rewire_input resets internal circuitry in case inputs changed.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
