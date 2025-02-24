/************************************************************
 * @file and3.hpp
 *
 * @brief Implements the And three bit microCircuit class, 
 *   which applies logic And to three input bits.
 ***********************************************************/
// Includes:
#include "microcircuit.hpp"
#include "and.hpp"

// Header Guards:
#ifndef AND3_H
#define AND3_H

namespace Virtual{

/**
 * @brief And3 is a three bit microCircuit with two And sub gates which outputs
 *   the three bit logic And in one output.
 *
 * And3 outputs 1 only if all three inputs are 1. It can simply be achieved by 
 * applying two And gates on the inputs A, B and C: And3{A,B,C} = (A And B) And C.
 *
 * @test Constructor, print_out and compute_output are tested in 3gate_test.
 */
class And3 : public microCircuit<3,1,2> {
  public:
    /**
     * @brief Constructor for And3 that sets the three inputs to the params, 
     *   creates two And gates and connects one with the first two inputs and then
     *   connects the output of the first And to the second And together with the
     *   third input, outputting the second And output.
     * @param conA first input bit.
     * @param conB second input bit.
     * @param conC third input bit.
     * @note inputs are completely symmetric.
     */
    And3(ptr_t conA = ground, ptr_t conB = ground, ptr_t conC = ground);

    /**
     * @brief rewire_input sets the two inputs of the first And gate and the second
     *   input of the second And gate to the three input_pointers_.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
