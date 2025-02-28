/************************************
 * @file full_adder.hpp
 *
 * @brief Implementation of the FullAdder circuit, which adds three bits, 
 ************************************/
// Include:
#include "microcircuit.hpp"
#include "or.hpp"
#include "half_adder.hpp"

// Header Guard:
#ifndef FULL_ADDER_H
#define FULL_ADDER_H

namespace Virtual{

/**
 * @brief FullAdder is a microCircuit that adds three bits together and outputs
 *   a two bit representation of the sum.
 *
 * FullAdder sums the three inputs and the first output corresponds to 2^0, while
 * the second output is 2^1, hence we can represent nrs 0 to 3. The internal 
 * circuit achieves this by adding the first two bits with a half adder and
 * then adding the third bit to the sum bit (first output bit of half adder) 
 * with another half adder. The sum bit output of the second output is directly
 * the 2^0 order bit, while applying an Or gate to the two overflow output bits
 * of the HalfAdder's gives the 2^1 order bit. E.g. Input 111, (11) added gives
 * 01 a zero sum but 1 overflow, then adding 1 to 0 gives 1 giving total output
 * 11 which as a binary number corresponds to 3.
 *
 * @test Constructor, print_out and compute_output are tested in hf_adder_test.cpp. 
 */
class FullAdder : public microCircuit<3,2,3> {
  public:
    /**
     * @brief Constructor of FullAdder sets the inputs and creates the circuit.
     * @param conA first summand.
     * @param conB second summand.
     * @param conC third summand.
     * @note Although the implementation is not symmetric in the inputs, the
     *   functionality is symmetric.
     */
    FullAdder(ptr_t conA = ground, ptr_t conB = ground, ptr_t conC = ground);

    /**
     * @brief rewire_input updates the inputs to the two HalfAdders according to
     *   the new input_pointers_.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
