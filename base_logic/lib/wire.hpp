/*************************************************************************************
 * @file wire.hpp
 *
 * @brief Implementation of the gate Wire mapping an in- to output bit without change.
 *************************************************************************************/
// Includes
#include "gate.hpp"

// Header Guard
#ifndef WIRE_H
#define WIRE_H

namespace Virtual{

/**
 * @brief Wire connects an input and an output bit writing the value of the input
 *   to the output.
 */
class Wire : public Gate<1,1> {
  public:
    /**
     * @brief Constructor initializes the input pointer with the parameter and creates
     *   an output std::shared_ptr.
     * @param input is a pointer to a bit which holds the input to the wire.
     */
    Wire(ptr_t input=ground);
    static const std::string gate_name;
    /**
     * @brief compute_output() writes the input bit value to the output bit.
     */
    void compute_output();
};

} //namespace Virtual
#endif
