/*****************************************
 * @file source_dest_decoder.hpp
 * 
 * @brief Implementation of SourceDestDecoder which decodes 
 *   the opcode of the Turing Complete architecture.
 *****************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "threebitdecoder.hpp"

// Header Guards:
#ifndef SOURCEDESTDECODER_H
#define SOURCEDESTDECODER_H

namespace Virtual{

/**
 * @brief SourceDestDecoder decodes an 8bit instruction set.
 *
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
class SourceDestDecoder : public byteMicroCircuit<0,1,20,0,4> {
  public:
    /**
     * @brief Constructor sets up the decoder.
     */
    SourceDestDecoder(ptr8_t input=ground8);

    /**
     * @brief rewire_input resets internal circuitry in case inputs changed.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
