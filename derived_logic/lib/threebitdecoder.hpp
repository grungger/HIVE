/****************************************************
 * @file threebitdecoder.hpp
 * 
 * @brief Implementation of a three bit Decoder gate.
 ****************************************************/
// Includes:
#include "microcircuit.hpp"
#include "and3.hpp"
#include "onebitdecoder.hpp"

// Header Guards:
#ifndef THREEBITDECODER_H
#define THREEBITDECODER_H

namespace Virtual{

/**
 * @brief ThreeBitDecoder is a three bit gate that decodes the input into its
 *   8 possible inputs (representable by 3 bits).
 * 
 * The ThreeBitDecoder gate interprets the three input bits as a binary number i 
 * and turns on the ith output, hence decoding the binary input. Note the first 
 * input bit corresponds to the lowest order of the binary number (2^0) while the
 * third bit corresponds to the highest order (2^2). So e.g. 000->10000000 and
 * 111->00000001, while 001->00001000 (note bits are in the order of input_pointers_
 * and output_pointers_ not bit significance).
 */
class ThreeBitDecoder : public microCircuit<3,8,11> {
  public:
    /**
     * @brief Constructor for the ThreeBitDecoder; the circuit is simply 
     *   the one bit decoding of each input bit and then a set of And3 gates
     *   each combining the right combination of inputs corresponding to output nr.
     * @param in1 is the first input with lowest order (2^0).
     * @param in2 is the second input with second lowest order (2^1).
     * @param in4 is the third input with highest order (2^2).
     * @note The order of the input matters, input bits are in ascending order.
     */
    ThreeBitDecoder(ptr_t in1=ground, ptr_t in2=ground, ptr_t in4=ground);

    /**
     * @brief rewire_input sets the inputs to the three OneBitDecoder gates to the
     *   corresponding input_pointers_ entry.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
