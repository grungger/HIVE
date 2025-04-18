/*********************************
 * @file word_nand.hpp
 *
 * @brief Implementation of ByteNAND and WordNAND.
 *********************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "nand.hpp"

// Header Guards:
#ifndef WORD_NAND_H
#define WORD_NAND_H

namespace Virtual{

/**
 * @brief ByteNAND implements the bitwise version of 
 *   the logic gate NAND for bytes.
 */
class ByteNAND : public byteMicroCircuit<0,2,0,1,11> {
  public:
    /**
     * @brief Constructor sets the bitwise architecture.
     * @param inA the first byte input.
     * @param inB the second byte input.
     */
    ByteNAND(ptr8_t inA=ground8, ptr8_t inB=ground8);

    /**
     * @brief rewire_input ensures the internal circuitry
     *   is conserved in case of a change in input pointers.
     */
    void rewire_input();

    static const std::string gate_name;
};


/**
 * @brief WordNAND implements the bitwise version of
 *   the logic gate NAND for words.
 */
class WordNAND : public wordMicroCircuit<0,0,2,0,0,1,35> {
  public:
    /**
     * @brief Constructor sets the bitwise operators.
     * @param inA the first input word.
     * @param inB the second input word.
     */
    WordNAND(ptr32_t inA=ground32, ptr32_t inB=ground32);
  
    /**
     * @brief rewire_input ensures the internal circuitry
     *   is conserved in case of a change in input pointers.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
