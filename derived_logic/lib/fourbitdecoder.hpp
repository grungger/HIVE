/****************************************************
 * @file fourbitdecoder.hpp
 * 
 * @brief Implementation of a four bit Decoder gate.
 ****************************************************/
// Includes:
#include "microcircuit.hpp"
#include "and.hpp"
#include "onebitdecoder.hpp"
#include "threebitdecoder.hpp"

// Header Guards:
#ifndef FOURBITDECODER_H
#define FOURBITDECODER_H

namespace Virtual{

/**
 * @brief FourBitDecoder is a four bit gate that decodes the input into its
 *   16 possible inputs (representable by 4 bits).
 * 
 * The FourBitDecoder gate interprets the four input bits as a binary number i 
 * and turns on the ith output, hence decoding the binary input. Note the first 
 * input bit corresponds to the lowest order of the binary number (2^0) while the
 * fourth bit corresponds to the highest order (2^3). So e.g. 0000->10..00 and
 * 1111->00..01 (note bits are in the order of input_pointers_
 * and output_pointers_ not bit significance).
 */
class FourBitDecoder : public microCircuit<4,16,18> {
  public:
    /**
     * @brief Constructor for the FourBitDecoder.
     * @param in1 is the first input with lowest order (2^0).
     * @param in2 is the second input with second lowest order (2^1).
     * @param in4 is the third input with second highest order (2^2).
     * @param in8 is the fourth input with highest order (2^3).
     * @note The order of the input matters, input bits are in ascending order.
     */
    FourBitDecoder(ptr_t in1=ground, ptr_t in2=ground, ptr_t in4=ground, ptr_t in8=ground);

    /**
     * @brief rewire_input sets the inputs to the ThreeBitDecoder and OneBitDecoder gates to the
     *   corresponding input_pointers_ entry.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
