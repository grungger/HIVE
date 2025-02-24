/*****************************
 * @file nor.hpp
 * 
 * @brief Implementation of the Nor gate (= Not ((Not A) Nand (Not B)) ) on two bits.
 */
// Includes:
#include "microcircuit.hpp"
#include "nand.hpp"
#include "not.hpp"

// Header Guards:
#ifndef NOR_H
#define NOR_H

namespace Virtual{

/**
 * @brief Nor is a two bit microCircuit with 4 components (3 Not, 1 Nand).
 *
 * Nor gate only outputs 1 if both inputs are 0, it acts like an And gate with
 * both inputs flipped, so it outputs (Not A) And (Not B) for inputs A and B.
 * This can also be written as Not[ (Not A) NAND (Not B) ], which is the way
 * it was implemented below.
 *
 * @test Constructor, print_out and compute_output are tested in 2gate_test.
 */
class Nor : public microCircuit<2,1,4> {
  public:
    /**
     * @brief Constructor for Nor setting inputs and creating Not, Not to Nand to Not
     *  subgate connections, finally settting output to the third Not output.
     * @param connectedA first input bit.
     * @param connectedB second input bit.
     * @note symmetric input.
     */
    Nor(ptr_t connectedA = ground, ptr_t connectedB = ground);

    /**
     * @brief rewire_input sets inputs of the first two Not gates to input_pointers_.
     */ 
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
