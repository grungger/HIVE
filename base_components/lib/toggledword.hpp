/***********************************************
 * @file toggledword.hpp
 * 
 * @brief Implementation of ToggledByte and ToggledWord.
 ***********************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "toggledbit.hpp"
#include "word_maker.hpp"
#include "word_wire.hpp"
#include "not.hpp"
#include "and.hpp"
#include "and3.hpp"
#include "wire.hpp"
#include "or.hpp"

// Header Guards:
#ifndef TOGGLEDWORD_H
#define TOGGLEDWORD_H

namespace Virtual{

/**
 * @brief ToggledByte implements the byte version of ToggledBit which
 *   writes the input byte to output iff bit input is on.
 *
 * ToggledByte overwrites the output byte in memory with the given 
 * input byte under the condition that the input bit is 1. Otherwise
 * the ToggledByte does nothing (in reality if input bit is 0 it reads
 * the in memory value of the output and writes that same value into
 * the output again, virtually doing nothing in the memory but still
 * executing a tick step). It performs bit toggling on each bit.
 * 
 * @test
 */
class ToggledByte : public byteMicroCircuit<1,1,0,1,37> {
  private:
    /**
     * @brief write0_ chooses whether toggled bit should write 0 if not
     *   toggled (true) or do nothing (false).
     */
    bool write0_;
  public:
    /**
     * @brief Constructor implements the circuit: splitting the
     *   input byte into bits and performing bitwise "toggling".
     * @param input the byte that is used to overwrite the memory.
     * @param toggle the toggling bit, overwriting is done if toggle=1.
     * @param write0 sets write0_ variable.
     * @note the byte input "input" is obsolete if toggle = False.
     */
    ToggledByte(ptr8_t input=ground8, ptr_t toggle=ground, bool write0=false);

    static const std::string gate_name;
    
    /**
     * @brief rewire input ensures that if the input pointers changed
     *   the internal circuitry is updated.
     */
    void rewire_input();

    /**
     * @brief connect_byte_output allows for reconnecting of the output.
     * 
     * connect_byte_output is a method unique to toggled gates which 
     * allows multiple instances of ToggledByte's to write to the same
     * output.
     * 
     * @param connected_output is the new byte output to write to.
     */
    void connect_byte_output(ptr8_t connected_output);
};


/**
 * @brief ToggledWord implements the word version of ToggledBit which 
 *   writes the input word to output iff bit input is on.
 *
 * ToggleWord overwrites the output word with the input word given that
 * the input bit is 1. If it is 0 it does nothing. The circuit
 * implementation is analoguously to ToggledByte with 32 ToggledBit's.
 *
 * @test
 */
class ToggledWord : public wordMicroCircuit<1,0,1,0,0,1,133> {
  private:
    /**
     * @brief write0_ chooses whether toggled bit should write 0 if not
     *   toggled (true) or do nothing (false).
     */
    bool write0_;
  public:
    /**
     * @brief Constructor that creates internal circuitry consisting 
     *   of 32 ToggledBit's.
     * @param word_input the input to overwrite with.
     * @param toggle the toggling bit.
     */
    ToggledWord(ptr32_t word_input=ground32, ptr_t toggle=ground, bool write0=false);

    static const std::string gate_name;

    /**
     * @brief rewire_input ensures that after changing the inputs,
     *   the internal circuitry is updated.
     */
    void rewire_input();

    /**
     * @brief connect_word_output allows for multiple ToggledWord's 
     *   to write to the same output.
     * @param connected_output the new output to write to.
     */
    void connect_word_output(ptr32_t connected_output);

    /**
     * @brief memory_release simply calls compute_output.
     */
    void memory_release();
};

} //namespace Virtual

#endif
