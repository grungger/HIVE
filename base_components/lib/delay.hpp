/*******************************************
 * @file delay.hpp
 *
 * @brief Implementation of the one bit delay gate.
 *******************************************/
// Includes:
#include "gate.hpp"

// Header Guards:
#ifndef DELAY_H
#define DELAY_H

namespace Virtual{

/*
 * @brief Delay is a one bit gate that writes the input to an internal save
 *   variable and outputs the previous value from last tick.
 * 
 * Delay is a basic gate that acts like a wire with a one-tick delay. An input
 * is outputted without change the next time compute_output is called. It does
 * this by saving the input to a private boolean variable save_ while
 * writing the previous save_ value to the output pointer. This way an input 
 * sequence 0 1 1 0 1 0 will output - 0 1 1 0 1, where the - indicates that
 * during the first use of the delay gate the save value will be initialized 
 * with 0 however if before an input sequence, the delay gate was already
 * in use the - will take the value of whatever was the last input.
 *
 * @test 
 */
class Delay : public Gate<1,1> {
  public:
    /*
     * @brief Constructor for Delay gate setting the input, initializing 
     *   the private variable save and creating an output bit initialised
     *   with 0.
     * @param connect is the input bit.
     */
    Delay(ptr_t connect = ground);

    static const std::string gate_name;
    
    /**
     * @brief compute_output sets the output to the save value bit and 
     *   overwrites the save bit with the current input.
     */
    void compute_output();
 
    /*
     * @brief memory_release is a method for gates that make use of memory; it
     *   can be used in larger circuits to set the output to the saved value,
     *   before having set the input bit, since memory_release only releases the
     *   saved value and doesnt overwrite with the input.
     */
    void memory_release();

  private:
    /*
     * @brief save_ holds the bit input value from the previous tick.
     */
    bool save_;
};

} //namespace Virtual

#endif
