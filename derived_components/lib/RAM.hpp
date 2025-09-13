/*******************************************
 * @file RAM.hpp
 *
 * @brief Implementation of RAM.
 *******************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "byte_decoder.hpp"
#include "or3.hpp"
#include "or.hpp"
#include "word_switch_in.hpp"
#include "toggledword.hpp"
#include <stdexcept>
#include <array>

#include <iostream>

// Header Guards:
#ifndef RAM_H
#define RAM_H

namespace Virtual{

/**
 * @brief RAM consists of 256 32-bit memory registers saved as an array accessible via their 8bit address.
 *
 * RAM allows for loading and saving 32bit words accessed via their address 0-255.
 */
class RAM : public wordMicroCircuit<0,0,2,0,0,2,9> {

  protected:
    /**
     * @brief RAM_lines saves the RAM memory.
     */
    std::array<word_t, 256> RAM_lines_;

  public:
    /**
     * @brief Constructor for RAM block where A and B are two input addresses and we need to distinguish between a copy and compute opcode.
     * @param full_opcode is the full program input word.
     * @param general_channel connected to all component outputs and represents the final input value after a copy operation.
     */
    RAM(ptr32_t full_opcode=ground32, ptr32_t general_channel=ground32);

    /**
     * @brief Moves words at addresses A and/or B to output A and B if COMPUTE mode or moves A to B or input to B or A to output if COPY mode.
     */
    void compute_output();

    /**
     * @brief rewire_input ensures internal circuitry is updated after inputs are changed.
     */
    void rewire_input();

    /**
     * @brief print RAM array (for debugging).
     */
    void printRAM();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
