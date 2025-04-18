/*********************************
 * @file word_nor.hpp
 *
 * @brief Implementation of ByteNor and WordNor.
 *********************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "nor.hpp"

// Header Guards:
#ifndef WORD_NOR_H
#define WORD_NOR_H

namespace Virtual{

/**
 * @brief ByteNor implements the bitwise version of 
 *   the logic gate Nor for bytes.
 */
class ByteNor : public byteMicroCircuit<0,2,0,1,11> {
  public:
    /**
     * @brief Constructor sets the bitwise architecture.
     * @param inA the first byte input.
     * @param inB the second byte input.
     */
    ByteNor(ptr8_t inA=ground8, ptr8_t inB=ground8);

    /**
     * @brief rewire_input ensures the internal circuitry
     *   is conserved in case of a change in input pointers.
     */
    void rewire_input();

    static const std::string gate_name;
};


/**
 * @brief WordNor implements the bitwise version of
 *   the logic gate Nor for words.
 */
class WordNor : public wordMicroCircuit<0,0,2,0,0,1,35> {
  public:
    /**
     * @brief Constructor sets the bitwise operators.
     * @param inA the first input word.
     * @param inB the second input word.
     */
    WordNor(ptr32_t inA=ground32, ptr32_t inB=ground32);
  
    /**
     * @brief rewire_input ensures the internal circuitry
     *   is conserved in case of a change in input pointers.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
