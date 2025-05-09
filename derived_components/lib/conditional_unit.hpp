/*****************************************
 * @file conditional_unit.hpp
 * 
 * @brief Implementation of ConditionalUnit which decodes 
 *   the opcode of the Turing Complete architecture and computes
 *   the condition.
 *****************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "threebitdecoder.hpp"
#include "not.hpp"
#include "word_not.hpp"
#include "word_adder.hpp"
#include "or.hpp"
#include "toggledbit.hpp"

// Header Guards:
#ifndef CONDITIONALUNIT_H
#define CONDITIONALUNIT_H

namespace Virtual{

/**
 * @brief ConditionalUnit decodes an 8bit instruction set and applies the condition.
 */
class ConditionalUnit : public byteMicroCircuit<0,2,1,0,18> {
  public:
    /**
     * @brief Constructor sets up the decoder.
     */
    ConditionalUnit(ptr8_t condition=ground8, ptr8_t input=ground8);

    /**
     * @brief rewire_input resets internal circuitry in case inputs changed.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
