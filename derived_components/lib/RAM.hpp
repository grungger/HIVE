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
#include <numeric>

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
class RAM : public wordMicroCircuit<3,2,1,0,0,2,6> {

  protected:
    /**
     * @brief RAM_lines saves the RAM memory.
     */
    std::array<word_t, 256> RAM_lines_;

  public:
    /**
     * @brief Constructor for RAM block where A and B are two input addresses and we need to distinguish between a copy and compute opcode.
     * @param computeCopyToggle determines whether RAM is accessed in copy or compute mode (in copy mode B is the save destination) (0=comp, 1=copy).
     * @param AloadToggle determines if the address A is interpreted as a RAM address, always performs a read-only load operation if toggled.
     * @param Btoggle determines whether B is interpreted as a RAM address, depending on which mode (compute or copy) it corresponds to load or save.
     * @param Aaddress the address of A input in RAM (given AloadToggle is true).
     * @param Baddress the address of B input in RAM (given Btoggle is true).
     * @param general_channel is the input word connected to the general CPU internal line.
     * @note The first output corresponds to A, the second output corresponds to B; they are toggled so nothing is written to the output
     *   if no load operation is performed.
     */
    RAM(ptr_t computeCopyToggle=ground, ptr_t AloadToggle=ground, ptr_t Btoggle=ground, 
	ptr8_t Aaddress=ground8, ptr8_t Baddress=ground8,
	ptr32_t general_channel=ground32 );

    /**
     * @brief Moves words at addresses A and/or B to output A and B if COMPUTE mode or moves A to B or input to B or A to output if COPY mode.
     */
    void compute_output();

    /**
     * @brief rewire_input ensures internal circuitry is updated after inputs are changed.
     */
    void rewire_input();

    /**
     * @brief memory_release simply releases the output (read-only operation).
     */
    void memory_release();

    /**
     * @brief full_compute assumes memory_release wasnt run before.
     */
    void full_compute();

    /**
     * @brief connect_word_output_i reroutes the toggledword method to the outer shell.
     * @param conOut the word location to connect to.
     * @param index a boolean to choose between output word A with index 0 (false) or B with 1 (true).
     * @note this is technically an overload of the BaseGate function connect_word_output, but
     *   that one does not allow for multiple outputs, hence I added _i to distinguish.
     */
    void connect_word_output_i(ptr32_t conOut, bool index);

    /**
     * @brief print RAM array (for debugging).
     */
    void printRAM();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
