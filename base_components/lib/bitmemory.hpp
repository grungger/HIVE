/***************************************
 * @file bitmemory.hpp
 *
 * @brief Implementation of the BitMemory gate, which can save a value
 *   and always outputs the saved value.
 ***************************************/
// Includes:
#include "microcircuit.hpp"
#include "delay.hpp"
#include "toggledbit.hpp"
#include "not.hpp"

// Header Guards:
#ifndef BITMEMORY_H
#define BITMEMORY_H

namespace Virtual{

/**
 * @brief BitMemory is a microCircuit that can save an input bit for
 *   arbitrarily long time - compared to Delay which saves a value for one tick,
 *   and outputs the saved value from last tick.
 *
 * BitMemory has two inputs - the first to enable saving, the second the actual
 * save value - and one output which always takes the value of the save value
 * at the start of the tick (i.e. if save is enabled the output will still be
 * the save value from last tick). The circuit is simple with two ToggledBit's
 * writing to the input of a delay line (where they are complementarily toggled
 * with save_enabler and Not(save_enabler)) with one writing the input value and
 * the other writing the save value from the delay line from last tick. This way
 * if save is not enabled the delay line will feed its own output to its input
 * retaining the "saved bit" value indefinitely until overwritten when save is
 * enabled. Note: the delay line is initially accessed via memory_release.
 *
 * @test Constructor, print_out, compute_output and memory_release are tested
 *   in bitmemory_test.cpp. 
 */
class BitMemory : public microCircuit<2,1,4> {
  public:
    /**
     * @brief Constructor sets inputs and implements the circuit.
     * @param save_enabler is the toggling bit to overwrite memory value
     *   with the input "save_value".
     * @param save_value is the input value; note this input is irrelevant if
     *   save_enabler is false.
     */
    BitMemory(ptr_t save_enabler=ground, ptr_t save_value=ground);

    /**
     * @brief rewire_input updates the inputs of the first ToggledBit as well
     *   as a Not gate based on input_pointers_.
     */
    void rewire_input();

    static const std::string gate_name;
 
    /**
     * @brief compute_output carries out one tick computation; since the second
     *   ToggledBit component requires the delay output as input, we first carry
     *   out a memory_release of the delay gate, then we compute_output of all
     *   components - overwriting the save value if save_enabler is on and
     *   outputting whatever was saved from the last tick.
     */
    void compute_output();

    /**
     * @brief memory_release simply releases the delay output.
     */
    void memory_release();
};

} //namespace Virtual

#endif
