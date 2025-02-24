/***************************************************************************
 * @file or.hpp
 *
 * @brief Implementation of the Or logic gate that applies Or on two inputs.
 ***************************************************************************/
// Includes:
#include "microcircuit.hpp"
#include "nand.hpp"
#include "not.hpp"

// Header Guards:
#ifndef OR_H
#define OR_H

namespace Virtual{

/**
 * @brief Or is a two bit microCircuit with three sub-gates (two Not and 
 *   one Nand gate) that outputs (inputA or inputB).
 * 
 * Or gate is only 0 if both inputs are 0. It can be implemented via
 * (Not A) NAND (Not B) for inputs A and B.
 *
 * @test Constructor, print_out and compute_output are tested in 2gate_test.
 */
class Or : public microCircuit<2,1,3> {
  public:
    /**
     * @brief Constructor for the Or gate that sets inputs, creates the sub-gates
     *   and connects the output of the Nand gate to the Or gate output.
     * @param connectedA first input bit.
     * @param connectedB second input bit.
     * @note symmetric inputs.
     */
    Or(ptr_t connectedA = ground, ptr_t connectedB = ground);

    /**
     * @brief rewire_input connects the input_pointers to the two Not sub-gates.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
