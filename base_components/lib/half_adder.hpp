/******************************************
 * @file half_adder.hpp
 * 
 * @brief Implementation of the HalfAdder circuit, which adds two bits.
 ******************************************/
// Includes:
#include "microcircuit.hpp"
#include "xor.hpp"
#include "and.hpp"

// Header Guards:
#ifndef HALF_ADDER_H
#define HALF_ADDER_H

namespace Virtual{

/**
 * @brief HalfAdder is a microCircuit that computes the sum of two input
 *   bits, and outputs the sum in one bit plus an overflow bit.
 *
 * HalfAdder takes two input bits sums them and outputs the output in two bits,
 * with increasing order (overflow bit is output_pointers_[1]). As a circuit
 * this is achieved by applying Xor to the inputs which becomes the lowest order
 * output bit (output_pointers_[0]) and also applying And to the inputs which
 * is the overflow bit value.
 *
 * @test
 */
class HalfAdder : public microCircuit<2,2,2> {
  public:
    /**
     * @brief Constructor sets inputs, creates Xor and And gates and sets outputs.
     * @param conA first summand input bit.
     * @param conB second summand input bit.
     * @note the inputs are handled symmetrically.
     */
    HalfAdder(ptr_t conA = ground, ptr_t conB = ground);

    /**
     * @brief rewire_input updates the inputs of the two subcomponents based
     *   on the new input_pointers_.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual;

#endif
