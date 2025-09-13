/********************************************
 * @file byte_decoder.hpp
 * 
 * @brief Implementation of ByteDecoder decoding a byte input into 256 possible outputs.
 ********************************************/
// Includes:
#include "wordmicrocircuit.hpp"

// Header Guards:
#ifndef BYTE_DECODER_H
#define BYTE_DECODER_H

namespace Virtual{

/**
 * @brief ByteDecoder takes a byte_t and decodes the input into 256 possible outputs. 
 */
class ByteDecoder : public byteMicroCircuit<0,1,256,0,0> {
  public:
    /**
     * @brief Constructor sets input and creates outputs.
     * @param conA the input byte.
     */
    ByteDecoder(ptr8_t conA = ground8);
    
    /**
     * @brief compute_output writes a 1 to the ith input (where i is the value of
     *   the input byte) and 0's everywhere else.
     */
    void compute_output();

    static const std::string gate_name;
};

} //namespace Virtual

#endif

