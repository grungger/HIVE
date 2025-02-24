/*******************************************************************************
 * @file and.hpp
 * 
 * @brief Implementation of the And logic gate that applies And to two inputs.
 *******************************************************************************/
// Includes:
#include "microcircuit.hpp"
#include "nand.hpp"
#include "not.hpp"

// Header Guards:
#ifndef AND_H
#define AND_H

namespace Virtual{

/**
 * @brief And is a two bit microCircuit with two components (NAND and Not gate) that
 *   outputs (inputA and inputB).
 *
 * And is a two bit microCircuit with one output and two sub-components. It acts as
 * the logic gate "And" outputting 1 only if both inputs are 1. It achieves this by
 * directly feeding the inputs into the NAND gate inputs and simply using Not on the
 * output, before outputting it to the And output.
 *
 * @test Constructor, print_out and compute_output are tested in 2gate_test.
 */
class And : public microCircuit<2,1,2> {
  public:
    /**
     * @brief Constructor for the And gate that sets the inputs to the params,
     *   creates a Nand gate, connects it to a created Not gate and sets the output
     *   to the Not output.
     * @param connectedA the first input bit (symmetric gate),
     * @param connectedB the second input bit (symmetric gate).
     */
    And(ptr_t connectedA = ground, ptr_t connectedB = ground);

    /**
     * @brief rewire input sets the Nand sub-gate's inputs to input_pointers_ 0 and 1.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
