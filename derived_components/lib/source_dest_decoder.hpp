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
