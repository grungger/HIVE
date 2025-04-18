/*********************************
 * @file word_neg.hpp
 *
 * @brief Implementation of ByteNeg and WordNeg.
 *********************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "not.hpp"
#include "word_not.hpp"
#include "word_adder.hpp"

// Header Guards:
#ifndef WORD_Neg_H
#define WORD_Neg_H

namespace Virtual{

/**
 * @brief ByteNeg implements the negation operator for bytes.
 *
 * ByteNeg uses the signed byte interpretation (using the highest
 * order bit as a negative value of -128 allowing for the range
 * between -128 to 127 compared to the unsigned 0 to 255) and
 * flips the sign of the integer value.
 */
class ByteNeg : public byteMicroCircuit<0,1,0,1,3> {
  public:
    /**
     * @brief Constructor sets the architecture.
     * @param in the input byte.
     */
    ByteNeg(ptr8_t in=ground8);

    /**
     * @brief rewire_input ensures the internal circuitry
     *   is conserved in case of a change in input pointers.
     */
    void rewire_input();

    static const std::string gate_name;
};


/**
 * @brief WordNeg implements the negation operator for words.
 */
class WordNeg : public wordMicroCircuit<0,0,1,0,0,1,3> {
  public:
    /**
     * @brief Constructor sets the architecture.
     * @param in the input word.
     */
    WordNeg(ptr32_t in=ground32);
  
    /**
     * @brief rewire_input ensures the internal circuitry
     *   is conserved in case of a change in input pointers.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
