/************************************
 * @file word_wire.hpp
 *
 * @brief Implementation of ByteWire and WordWire.
 ***********************************/
// Includes:
#include "wordmicrocircuit.hpp"

// Header Guards:
#ifndef WORD_WIRE_H
#define WORD_WIRE_H

namespace Virtual {

/**
 * @brief ByteWire is the byte implementation of Wire.
 */
class ByteWire : public byteMicroCircuit<0,1,0,1,0> {
  public:
    /**
     * @brief Constructor sets input and creates output.
     * @param input the input byte.
     */
    ByteWire(ptr8_t input=ground8);

    /**
     * @brief Constructor sets both input and output.
     * @param input the input byte.
     * @param output the specified location where the wire writes to.
     */
    ByteWire(ptr8_t input, ptr8_t output);

    static const std::string gate_name;

    /**
     * @brief compute_output writes input byte to output byte without
     *   alteration.
     */
    void compute_output();
};


/**
 * @brief WordWire is the word implementation of Wire.
 */
class WordWire : public wordMicroCircuit<0,0,1,0,0,1,0> {
  public:
    /**
     * @brief Constructor sets input and creates output.
     * @param input the input byte.
     */
    WordWire(ptr32_t input=ground32);

    /**
     * @brief Constructor sets both input and output.
     * @param input the input byte.
     * @param output the output byte.
     */
    WordWire(ptr32_t input, ptr32_t output);

    static const std::string gate_name;

    /**
     * @brief compute_output writes input word to output.
     */
    void compute_output();
};

} //namespace Virtual

#endif
