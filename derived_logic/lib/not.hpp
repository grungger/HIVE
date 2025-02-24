/*****************************************************************************
 * @file not.hpp
 *
 * @brief Implementation of the Not logic gate, that applies not on one input.
 *****************************************************************************/
// Includes:
#include "microcircuit.hpp"
#include "nand.hpp"

// Header Guard:
#ifndef NOT_H
#define NOT_H

namespace Virtual{

/**
 * @brief Not is a one bit microCircuit with one component (a NAND gate) that 
 *   outputs the opposite output as the input.
 *
 * Not is a one bit microCircuit with one sub-component and one output. It corresponds
 * to a bit-flip on the input bit i.e. it maps 0 to 1 and 1 to 0. The internal logic consists of
 * simply connecting the input to both inputs of the NAND gate giving the desired output.
 *
 * @test Constructor, print_out and compute_output are tested in 2gate_test.
 */
class Not : public microCircuit<1,1,1> {
  public:
    /**
     * @brief Constructor for the Not gate that sets the input to the param, creates
     *   a NAND gate as a microCircuit (with the input connected to both NAND inputs)
     *   and sets the output to the NAND output.
     * @param connected is the input bit that can be provided, default is ground.
     */
    Not(ptr_t connected = ground);

    /**
     * @brief rewire_input sets the NAND gate inputs to input_pointers_[0] - should
     *   be used in case the input is changed (if done with connect_input, it is
     *   called automatically).
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
