/*****************************************
 * @file word_and.hpp
 * 
 * @brief Implementation of ByteAnd and WordAnd to And two bytes/words.
 *****************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "and.hpp"

// Header Guards:
#ifndef WORD_AND_H
#define WORD_AND_H

namespace Virtual{

/**
 * @brief ByteAnd applies bitwise logical And on two input bytes.
 */
class ByteAnd : public byteMicroCircuit<0,2,0,1,11> {
  public:
    /**
     * @brief Constructor sets up bitwise And by splitting into bits.
     */
    ByteAnd(ptr8_t inA=ground8, ptr8_t inB=ground8);

    /**
     * @brief rewire_input resets internal circuitry in case inputs changed.
     */
    void rewire_input();

    static const std::string gate_name;
};


/**
 * @brief WordAnd applies bitwise logical And to two input words.
 */
class WordAnd : public wordMicroCircuit<0,0,2,0,0,1,35> {
  public:
    /**
     * @brief Constructor sets up bitwise And by splitting into bits.
     */
    WordAnd(ptr32_t inA=ground32, ptr32_t inB=ground32);

    /**
     * @brief rewire_input resets internal circuitry in case inputs changed.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
