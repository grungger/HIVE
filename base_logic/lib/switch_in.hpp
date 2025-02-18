/************************************************************************
 * @file switch_in.hpp
 *
 * @brief Implementation of the gate Switch_in which is a constant input
 *   with a switchable value.
 ************************************************************************/

// Includes
#include "gate.hpp"

// Header Guard
#ifndef SWITCH_IN_H
#define SWITCH_IN_H

namespace Virtual{

/**
 * @brief Switch_in is a gate with only one bit output that can be toggled on or off.
 * 
 * The class Switch_in is an input gate with a constant value (false by default)
 * that can be toggled on or off via the method change_state. Calling compute_output()
 * simply writes the saved state_ value to the output bit.
 */
class Switch_in : public Gate<0,1> {
  public:
    /**
     * @brief Constructor for the class; which creates a std::shared_ptr for the output.
     */
    Switch_in(bool=false);
    /**
     * @brief gate_name saves the name of this class of gates.
     */
    static const std::string gate_name;
    /**
     * @brief compute_output writes the current state_ to the output bit.
     */
    void compute_output();
    /**
     * @brief change_state overwrites the state_ variable with the parameter.
     * @param new_state the state with which to overwrite the current state_.
     * @note compute_output is automatically invoked for convenience.
     */
    void change_state(bool);
    
  private:
    /**
     * @brief state_ holds the current value of the output bit.
     */
    bool state_;
};

} //namespace Virtual
#endif
