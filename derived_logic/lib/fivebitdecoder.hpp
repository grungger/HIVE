/****************************************************
 * @file fivebitdecoder.hpp
 * 
 * @brief Implementation of a five bit Decoder gate.
 ****************************************************/
// Includes:
#include "microcircuit.hpp"
#include "and.hpp"
#include "onebitdecoder.hpp"
#include "fourbitdecoder.hpp"

// Header Guards:
#ifndef FIVEBITDECODER_H
#define FIVEBITDECODER_H

namespace Virtual{

/**
 * @brief FiveBitDecoder is a five bit gate that decodes the input into its
 *   32 possible inputs (representable by 5 bits).
 * 
 * The FiveBitDecoder gate interprets the five input bits as a binary number i 
 * and turns on the ith output, hence decoding the binary input. Note the first 
 * input bit corresponds to the lowest order of the binary number (2^0) while the
 * fifth bit corresponds to the highest order (2^4).
 */
class FiveBitDecoder : public microCircuit<5,32,32> {
  public:
    /**
     * @brief Constructor for the FiveBitDecoder.
     * @param in1 is the first input with lowest order (2^0).
     * @param in2 is the second input with second lowest order (2^1).
     * @param in4 is the third input with third highest order (2^2).
     * @param in8 is the fourth input with second highest order (2^3).
     * @param in16 is the fifth input with highest order (2^4).
     * @note The order of the input matters, input bits are in ascending order.
     */
    FiveBitDecoder(ptr_t in1=ground, ptr_t in2=ground, ptr_t in4=ground, ptr_t in8=ground, ptr_t in16=ground);

    /**
     * @brief rewire_input resets the inputs.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
