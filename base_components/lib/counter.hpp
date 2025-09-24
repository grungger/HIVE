/***********************************************
 * @file counter.hpp
 *
 * @brief Implementation of the ByteCounter byteMicroCircuit that tells a program block, 
 *   which instruction to run next, increments every tick and can be overwritten, and
 *   the word analog Counter.
 **********************************************/
// Includes: 
#include "wordmicrocircuit.hpp"
#include "word_mux.hpp"
#include "word_memory.hpp"
#include "word_adder.hpp"
#include "not.hpp"

// Header Guards:
#ifndef COUNTER_H
#define COUNTER_H

namespace Virtual{

/**
 * @brief ByteCounter contains a ByteMemory to save a counter value,
 *   starting at value 0 and incrementing continuously; it also allows
 *   for overwriting the counter with the byte input by setting the 
 *   bit input to 1.
 */
class ByteCounter : public byteMicroCircuit<1,1,0,1,4> {
  public:
    /**
     * @brief Constructor sets inputs and prepares counter memory.
     */
    ByteCounter(ptr_t overwrite=ground, ptr8_t value=ground8);
   
    /**
     * @brief rewire_input ensures the internal circuitry is conserved,
     *   if the input pointers changed.
     */
    void rewire_input();

    static const std::string gate_name;

    /**
     * @brief compute_output is an overloading of the byteMicroCircuit method,
     *   since the presence of a memory block requires a memory_release in between.
     */
    void compute_output();

    /**
     * @brief memory_release ensures that the memory components write the current
     *   value to their respective output.
     */
    void memory_release();
};


/**
 * @brief Counter contains a WordMemory to save a counter Word,
 *   starting at 0 and incrementing every tick; also allowing the
 *   value to be overwritten with the word input by setting the 
 *   input bit to 1.
 */
class Counter : public wordMicroCircuit<1,0,1,0,0,1,4> {
  public:
    /**
     * @brief Constructor sets inputs and prepares counter memory.
     */
    Counter(ptr_t overwrite=ground, ptr32_t value=ground32);

    /**
     * @brief rewire_input ensures the internal circuitry is conserved,
     *   if the input pointers changed.
     */
    void rewire_input();

    static const std::string gate_name;

    /**
     * @brief compute_output is the overloaded version of the byteMicroCircuit method,
     *   since the presence of a memory block requires the use of memory_release.
     */
    void compute_output();

    /**
     * @brief memory_release releases the memory component outputs to their respective
     *   outputs.
     */
    void memory_release();

    /**
     * @brief memory_receive carries out the memory overwrite but doesnt add 
     *   to the counter.
     */
    void memory_receive();
};

}
#endif
