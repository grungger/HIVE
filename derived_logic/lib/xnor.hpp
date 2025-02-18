/******************************
 * @file xnor.hpp
 *
 * @brief Implementation of the Xnor gate (= Not (A Xor B)) on two bits.
 */
// Includes_
#include "microcircuit.hpp"
#include "xor.hpp"
#include "not.hpp"

// Header Guards:
#ifndef XNOR_H
#define XNOR_H

namespace Virtual{

/**
 * @brief Xnor is a two bit microCircuit gate with 2 subgates (Xor, Not).
 */
class Xnor : public microCircuit<2,1,2> {
  public:
    /**
     * @brief Constructor for Xnor gate connecting inputs, creating Xor, Not gates,
     *   and setting output to Not output.
     * @param connectedA first input bit.
     * @param connectedB second input bit.
     * @note symmetric inputs.
     */
    Xnor(ptr_t connectedA = ground, ptr_t connectedB = ground);
  
    /**
     * @brief rewire_input sets two Xor inputs two input_pointers_.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
