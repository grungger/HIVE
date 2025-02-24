/***************************************
 * @file bitmemory.hpp
 *
 * @brief Implementation of the BitMemory gate, which can save a value
 *   and always outputs the saved value.
 ***************************************/
// Includes:
#include "bytemicrocircuit.hpp"
#include "delay.hpp"
#include "toggledbit.hpp"
#include "not.hpp"

// Header Guards:
#ifndef BITMEMORY_H
#define BITMEMORY_H

namespace Virtual{

/**
 * @brief BitMemory is a microCircuit that can save an input bit for
 *   arbitrarily long time - compared to Delay which saves a value for one tick.
 */
class BitMemory : public microCircuit<2,1,4> {
  public:
    /**
     * @brief Constructor sets inputs and implements the circuit: the
     *   save_enabler input toggles a ToggledBit with the value save_value,
     *   its output is routed into a delay gate. Another ToggledBit is toggled
     *   via Not(save_enabler) with the delay gate output as value. Its output
     *   is rerouted with connect_output method of ToggledBit gates to also 
     *   write to the delay input. In conclusion save_enabler toggles between
     *   giving the last delay value to the delay input or the new save value.
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
