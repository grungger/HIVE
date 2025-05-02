/*************************************************
 * @file toggledbit.hpp
 *
 * @brief Implementation of the ToggledBit.
 ************************************************/
// Includes:
#include "microcircuit.hpp"
#include "not.hpp"
#include "and.hpp"
#include "and3.hpp"
#include "wire.hpp"
#include "or.hpp"

// Header Guards:
#ifndef TOGGLEDBIT_H
#define TOGGLEDBIT_H

namespace Virtual{

/**
 * @brief ToggledBit is a two bit gate that writes input 1 to output iff input 2 is 1.
 *
 * ToggledBit overwrites the output bit with the first input if the second input is 1 -
 * think of an output as a pointer to a bit in memory, where "outputting a value" means
 * overwriting the old bit value with the output value. The ToggledBit acts as a wire
 * if the second input is 1 but does nothing (does not overwrite the bit in memory) if
 * the second input is 0. This allows for a unique feature of this gate where two
 * ToggledBit's can be rewired via connect_output method to have their outputs point
 * to the same memory address consequentially overwriting with only one of the values
 * depending on the logic of the circuit. Ideally max two ToggledBits should connect
 * to one memory address and their toggle input should be complimentary to avoid 
 * undefined memory overwriting (if both gates are writing to memory in a single tick,
 * the final memory value depends on the internal implementation order and 
 * is generally undefined). The actual implementation is done in a roundabout way,
 * while originally it was simply done with a C++-if-statement, it is now built as
 * a microcircuit. If you create a connection from the output to the input then you
 * can toggle between two bits: either overwrite the output with the new value,
 * or "overwrite" the output with the output, hence doing nothing. This can be done
 * via the logic (with O the old output, V the new value and T the toggling bit):
 * ToggledBit(V,T) = (T And V) Or ((Not T) And O). to avoid problems with directly
 * adding an output pointer to an input pointer there is also a Wire right before the
 * output to add a layer of abstraction.
 *
 * @test Constructor, print_in, print_out, connect_output and compute_output are tested
 *   in toggledbit_test.
 */
class ToggledBit : public microCircuit<2,1,6>  {
  private:
    /**
     * @brief write0_ chooses whether toggled bit should write 0 if not
     *   toggled (true) or do nothing (false).
     */
    bool write0_;
  public:
    /**
     * @brief Constructor for the ToggledBit gate, creates the internal circuitry and
     *   connects in- and outputs - it contains a Not gate, two And gates, a Wire and 
     *   an Or gate.
     * @param conIn the first input bit - the value to overwrite the output with.
     * @param conTog the second input bit - the toggling bit.
     * @param write0 sets write0_ variable.
     */
    ToggledBit(ptr_t conIn=ground, ptr_t conTog=ground, bool write0=false);

    static const std::string gate_name;

    /**
     * @brief connect_output changes where the object writes the output to a new memory
     *   location, allowing for several ToggledBit's pointing to the same location.
     * @param connected_output the new output pointer.
     * @note We make use of the Wire functionality to be constructed with a preexisting
     *   output bit; connect_output creates a new Wire component in memory, hence 
     *   has a small memory overhead.
     */
    void connect_output(ptr_t connected_output);

    /**
     * @brief rewire_input updates the Not and one And gate inputs with input_pointers_.
     */
    void rewire_input();
};

} //namespace Virtual

#endif
