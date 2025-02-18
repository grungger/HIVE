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
