/*****************************************************************************
 * @file xor.hpp
 *
 * @brief Implementation of Xor gate (= (A Nor B) Nor (A And B)) for two bits.
 *****************************************************************************/
// Includes:
#include "microcircuit.hpp"
#include "nor.hpp"
#include "and.hpp"

// Header Guards:
#ifndef XOR_H
#define XOR_H

namespace Virtual{

/**
 * @brief Xor is a two bit microCircuit with three sub-gates (2 Nor, 1 And).
 */
class Xor : public microCircuit<2,1,3> {
  public:
    /**
     * @brief Constructor for Xor gate setting inputs, creating Nor and And gates
     *   both acting on input params, and another Nor acting on previous two subgates
     *   and setting outputs to last Nor gate output.
     * @param connectedA first input bit.
     * @param connectedB second input bit.
     * @note symmetric input.
     */ 
    Xor(ptr_t connectedA = ground, ptr_t connectedB = ground);
 
    /**
     * @brief rewire_input sets input_pointers_ to Nor and And gate inputs.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
