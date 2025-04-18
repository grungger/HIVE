/****************************************************
 * @file word_output.hpp
 *
 * @brief Implementation of ByteOutput and WordOutput to create byte and word sinks.
 ****************************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include <iostream>

// Header Guards:
#ifndef WORDOUTPUT_H
#define WORDOUTPUT_H

namespace Virtual{

/**
 * @brief ByteOutput is a sink to std::cout, prints a byte input to std::cout.
 */
class ByteOutput : public byteMicroCircuit<0,1,0,0,0> {
  public:
    /**
     * @brief Constructor for the output block.
     * @param connector the input byte.
     */
    ByteOutput(ptr8_t connector=ground8);

    static const std::string gate_name;

    /**
     * @brief compute_output prints the input to std::cout, uses the overloaded << of byte_t.
     */
    void compute_output();

    /**
     * @brief printf_out print the number of the output with the byte_t value.
     */
    void printf_out();

  private:
    /**
     * @brief counter_ to keep track of how many outputs were created.
     */
    static int counter_;

    /**
     * @brief id_ is the current value of the counter_ to give a unique id.
     */
    const int id_;
};


/**
 * @brief WordOutput is a sink to std::cout, prints to std::cout.
 */
class WordOutput : public wordMicroCircuit<0,0,1,0,0,0,0> {
  public:
    /**
     * @brief Constructor creates the output.
     */
    WordOutput(ptr32_t connector=ground32);

    static const std::string gate_name;

    /**
     * @brief compute_output prints the input to std::cout, uses overloaded << of word_t.
     */
    void compute_output();

    /**
     * @brief printf_out print the output id and value of output.
     */
    void printf_out();

  private:
    /**
     * @brief counter to keep track of how many outputs were created.
     */
    static int counter_;

    /**
     * @brief id_ is the current value of the counter_ to give a unique id.
     */
    const int id_;
};

} //namespace Virtual

#endif
