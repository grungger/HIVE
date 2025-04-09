/**********************************
 * @file word_mux.hpp
 * 
 * @brief Implementation of ByteMUX and WordMUX.
 **********************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "toggledword.hpp"
#include "not.hpp"

// Header Guards:
#ifndef WORD_MUX_H
#define WORD_MUX_H

namespace Virtual{

/**
 * @brief ByteMUX implements a switch between two bytes.
 *
 * ByteMUX allows the switching betweent two byte inputs,
 * by selecting them with an input bit (bit value 0 selects
 * the first byte input and value 1 selects the second).
 */
class ByteMUX : public byteMicroCircuit<1,2,0,1,3> {
  public:
    /**
     * @brief Constructor implements the circuitry toggling the input bytes.
     * @param toggler the input bit to switch between inA and inB.
     * @param inA byte selected for toggler==0.
     * @param inB byte selected for toggler==1.
     */
    ByteMUX(ptr_t toggler=ground, ptr8_t inA=ground8, ptr8_t inB=ground8);

    /**
     * @brief rewire_input ensures the internal circuitry is conserved,
     *   in case the input changes.
     */
    void rewire_input();

    static const std::string gate_name;

};


/**
 * @brief WordMUX implements a switch between two words.
 *
 * WordMUX allows the switching between two word inputs,
 * by toggling between them with a bit (bit value 0
 * selects the first input word, bit value 1 selects
 * the second input word).
 */
class WordMUX : public wordMicroCircuit<1,0,2,0,0,1,3> {
  public:
    /**
     * @brief Constructor implements the circuitry toggling the input words.
     * @param toggler the input bit to switch between inA and inB.
     * @param inA word selected for toggler==0.
     * @param inB word selected for toggler==1.
     */
    WordMUX(ptr_t toggler=ground, ptr32_t inA=ground32, ptr32_t inB=ground32);

    /**
     * @brief rewire_input ensures the internal circuitry is conserved. 
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
