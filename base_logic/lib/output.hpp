/************************************************************************
 * @file output.hpp
 * 
 * @brief Implementation of the gate Output which maps an input bit to std::ostream.
 ************************************************************************/
// Includes
#include <iostream>
#include "gate.hpp"

// Header Guard
#ifndef OUTPUT_H
#define OUTPUT_H

namespace Virtual{

/**
 * @brief Output is a gate with only one input bit which is outputted to std::ostream.
 */ 
class Output : public Gate<1,0> {
  public:
    /**
     * @brief Constructor initializes the input pointer with the given parameter.
     * @param connected an existing pointer to the input bit - ground by default.
     */
    Output(ptr_t connected = ground);
    static const std::string gate_name;
    /**
     * @brief compute_output prints the value of the input bit to std::ostream
     */
    void compute_output();
    /**
     * @brief printf_out also prints the input bit to std::ostream but adds
     *   the id of the object to the output.
     */
    void printf_out();
  
  private:
    /**
     * @brief For convenience to differentiate Output std::ostream outputs we add an ID.
     */
    static int counter_;
    const int id_;
};

} //namespace Virtual

#endif
