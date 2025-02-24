/*************************************************
 * @file toggledbit.hpp
 *
 * @brief Implementation of the ToggledBit.
 */
#include "gate.hpp"
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
 * is generally undefined).
 *
 * @note This gate is a basic gate where the internal logic is written via a
 *   conditional...
 * @test
 */
class ToggledBit : public Gate<2,1>  {
  public:
    /**
     * @brief Constructor for the ToggledBit gate
    ToggledBit(ptr_t conIn=ground, ptr_t conTog=ground);
    static const std::string gate_name;
    void compute_output();
    void connect_output(ptr_t connected_output);
};

} //namespace Virtual

#endif
