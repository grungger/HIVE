/**********************************
 * @file word_switch_in.hpp
 * 
 * @brief Implementation of ByteSwitch_in and WordSwitch_in.
 ***********************************/
// Includes:
#include "wordmicrocircuit.hpp"

// Header Guards:
#ifndef BYTESWITCH_IN_H
#define BYTESWITCH_IN_H

namespace Virtual{

/**
 * @brief ByteSwitch_in is a simple byte input source that can have its value changed.
 */
class ByteSwitch_in : public byteMicroCircuit<0,0,0,1,0> {
  public:
    /**
     * @brief Constructor of the input with a byte_t value.
     */
    ByteSwitch_in(byte_t);

    /**
     * @brief Constructor of the input via std::uint8_t and default constructor with 0.
     */
    ByteSwitch_in(std::uint8_t=0);

    static const std::string gate_name;

    /**
     * @brief compute_output sets the memory location to the internal state variable.
     */
    void compute_output();
    
    /**
     * @brief change_state sets a new input value with byte_t or std::uint8_t.
     */
    void change_state(byte_t);
    void change_state(std::uint8_t);

  private:
    /**
     * @brief state_ saves the byte_t.
     */
    byte_t state_;
};


/**
 * @brief WordSwitch_in is a simple word input source that can have its value changed.
 */
class WordSwitch_in : public wordMicroCircuit <0,0,0,0,0,1,0> {
  public:
    /**
     * @brief Constructor of the input with a word_t value.
     */
    WordSwitch_in(word_t);

    /**
     * @brief Constructor of the input  with a std::uint32_t and constructor with 0.
     */
     WordSwitch_in(std::uint32_t=0);

    static const std::string gate_name;

    /**
     * @brief compute_output sets the memory location to the internal state variable.
     */
    void compute_output();

    /**
     * @brief change_state sets a new input value with word_t or std::uint32_t.
     */
     void change_state(word_t);
     void change_state(std::uint32_t);

  private:
    /**
     * @brief state_ saves the word_t.
     */
    word_t state_;
};

} //namespace Virtual

#endif
