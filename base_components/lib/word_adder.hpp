/********************************************
 * @file word_adder.hpp
 * 
 * @brief Implementation of ByteAdder and WordAdder to add two bytes/words and
 *   an additional bit (a carry).
 ********************************************/ 
// Includes:
#include "wordmicrocircuit.hpp"
#include "full_adder.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"

// Header Guards:
#ifndef WORD_ADDER_H
#define WORD_ADDER_H

namespace Virtual{

/**
 * @brief ByteAdder takes two bytes and one bit and adds them together into
 *   one byte for the sum and a potential carry as a bit.
 */
class ByteAdder : public byteMicroCircuit<1,2,1,1,11> {
  public:
    /**
     * @brief Constructor sets the inputs and creates the FullAdder components.
     * @param inbit the bit input to be added
     * @param sumA first input byte to sum
     * @param sumB second input byte to sum
     */
    ByteAdder(ptr_t inbit=ground, ptr8_t sumA=ground8, ptr8_t sumB=ground8);

    /**
     * @brief rewire_input ensures that after changing input pointers,
     *   the internal circuitry is conserved.
     */ 
    void rewire_input();

    static const std::string gate_name;
};


/**
 * @brief WordAdder takes two words and one bit and adds them together
 *   into one word output and an additional carry bit.
 */
class WordAdder : public wordMicroCircuit<1,0,2,1,0,1,35> {
  public:
    /**
     * @brief Constructor sets inputs and FullAdder components.
     * @param inbit the bit input to be added
     * @param inwordA the first word input to be added
     * @param inwordB the second word input to be added
     */
    WordAdder(ptr_t inbit=ground, ptr32_t inwordA=ground32, ptr32_t inwordB=ground32);

    /**
     * @brief rewire_input ensures the internal circuitry is conserved after changing
     *   input pointers.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
