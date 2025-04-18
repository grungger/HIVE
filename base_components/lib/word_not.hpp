/*********************************
 * @file word_not.hpp
 *
 * @brief Implementation of ByteNot and WordNot.
 *********************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "not.hpp"

// Header Guards:
#ifndef WORD_Not_H
#define WORD_Not_H

namespace Virtual{

/**
 * @brief ByteNot implements the bitwise version of 
 *   the logic gate Not for bytes.
 */
class ByteNot : public byteMicroCircuit<0,1,0,1,10> {
  public:
    /**
     * @brief Constructor sets the bitwise architecture.
     * @param in, the byte input.
     */
    ByteNot(ptr8_t in=ground8);

    /**
     * @brief rewire_input ensures the internal circuitry
     *   is conserved in case of a change in input pointers.
     */
    void rewire_input();

    static const std::string gate_name;
};


/**
 * @brief WordNot implements the bitwise version of
 *   the logic gate Not for words.
 */
class WordNot : public wordMicroCircuit<0,0,1,0,0,1,34> {
  public:
    /**
     * @brief Constructor sets the bitwise operators.
     * @param in, the input word.
     */
    WordNot(ptr32_t in=ground32);
  
    /**
     * @brief rewire_input ensures the internal circuitry
     *   is conserved in case of a change in input pointers.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
