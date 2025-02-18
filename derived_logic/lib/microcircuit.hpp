/**********************************************************************
 * @file microcircuit.hpp
 * 
 * @brief Implementation of the base template class microCircuit,
 *   consisting of several Gate instances.
 **********************************************************************/
// Includes:
#include "gate.hpp"

// Header guard:
#ifndef MICROCIRCUIT_H
#define MICROCIRCUIT_H

namespace Virtual{

/**
 * @brief Basic implementation of a small component consisting of several gates.
 * 
 * microCircuit implements a logic gate that consists of N_comp-nr of gates,
 * which are connected in a way to produce a more complicated functionality.
 *
 * @tparam N_in the number of input bits.
 * @tparam N_out the number of output bits.
 * @tparam N_comp the number of gates that make up the microCircuit.
 */
template <io_t N_in, io_t N_out, io_t N_comp>
class microCircuit : public Gate<N_in, N_out> {
  protected:
    /**
     * @brief circuit_components_ holds the list of pointers to all sub-gates.
     */
    std::array<std::shared_ptr<BaseGate>,N_comp> circuit_components_;

  public:
    /**
     * @brief prints all names (the member 'gate_name' of sub-gates.
     */
    void print_components() {
      for(auto it=circuit_components_.begin(); it<circuit_components_.end(); it++) {
        std::cout << (*it)->gate_name << std::endl;
      }
    }
    
    /**
     * @brief Overloaded member function of Gate-class to allow complicated
     *   input connectivity to be rewired via rewire_input method.
     * @param connected_output is the new output to set the (index)th input.
     * @param index sets which input is changed to the new bit.
     * @exception std::domain_error exception thrown in case index is out of range.
     */
    void connect_input(ptr_t connected_output, io_t index) {
      if (index >= N_in) {
        throw std::domain_error("Input that was attempted to connect is out of range");
      }
      this->input_pointers_[index] = connected_output;
      if (N_comp>=1) {
        rewire_input();
      }
    }
   
    /**
     * @brief Virtual member function that ensures the sub-gates are connected to
     *   the input bits listed in the input_pointers_ array.
     */
    virtual void rewire_input() {};

    /**
     * @brief Overloaded member function of Gate-class to run the same function for
     *   all sub-gates in the microCircuit.
     */
    void compute_output() {
      for(auto it=circuit_components_.begin(); it<circuit_components_.end(); it++) {
        (*it)->compute_output();
      }
    }
};

} //namespace Virtual

#endif
