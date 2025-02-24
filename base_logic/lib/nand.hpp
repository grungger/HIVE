/*******************************************************************************
 * @file nand.hpp
 * 
 * @brief Implementation of the NAND logic gate, that applies nand on two inputs.
 *******************************************************************************/

// Includes
#include "gate.hpp"

// Header Guard
#ifndef NAND_H
#define NAND_H

namespace Virtual{

/**
 * @brief NAND is a two bit gate that outputs nand of the inputs.
 *
 * NAND is a two bit gate that computes "not and" on two inputs 
 * and writes to an output.
 *
 * @test Constructor, print_in, print_out and compute_output are tested in logictest1.cpp
 *   with corresponding Make name "nand_test".
 */
class NAND : public Gate<2,1> {
  public:
    /**
     * @brief Constructor initializes two input pointers and creates a shared 
     *   output pointer that is initialized with in1 nand in2.
     */
    NAND(ptr_t connected1 = ground, ptr_t connected2 = ground);
    static const std::string gate_name;
    /**
     * @brief compute_output simply writes (!in1)&&(!in2) for the two input bits
     *   to the output bit.
     */
    void compute_output();
};

} //namespace Virtual
#endif
