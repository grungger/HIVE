/**********************************************
 * @file onebitdecoder.hpp
 *
 * @brief Implementation of a One-bit-Decoder turning on output i if input is i.
 */
// Includes:
#include "microcircuit.hpp"
#include "wire.hpp"
#include "not.hpp"

// Header Guards:
#ifndef ONEBITDECODER_H
#define ONEBITDECODER_H

namespace Virtual{

/**
 * @brief OneBitDecoder is a one bit gate that decodes the input.
 *
 * The OneBitDecoder decodes the input - decoding meaning, given any input
 * there is exactly one unique output channel turned on - so 0 maps to 1,0 and
 * 1 maps to 0,1 (see ThreeBitDecoder for an extended version).
 */
class OneBitDecoder : public microCircuit<1,2,2> {
  public:
    /**
     * @brief Constructor for the OneBitDecoder sets the input, creates a Not gate
     *   and a Wire and connects their outputs to the outputs in the same order.
     * @param input is the input bit.
     */
    OneBitDecoder(ptr_t input=ground);

    /**
     * @brief rewire_input sets the Not and Wire gate inputs to input_pointers_.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
