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
     * @brief Constructor
     */
    ByteAnd(ptr32_t inA=ground32, ptr32_t inB=ground32);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
