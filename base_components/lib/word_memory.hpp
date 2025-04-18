/**********************************
 * @file word_memory.hpp
 *
 * @brief Implementation of ByteMemory WordMemory.
 **********************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "bitmemory.hpp"
#include "word_splitter.hpp"
#include "word_maker.hpp"
#include "toggledword.hpp"

// Header Guards:
#ifndef WORD_MEMORY_H
#define WORD_MEMORY_H

namespace Virtual{

/**
 * @brief ByteMemory can save an input byte for arbitrarily long time.
 * 
 * ByteMemory takes a byte input to overwrite the save value with; the
 * overwrite occurs if the save bit input is set to one. If load is enabled
 * the gate will write the current value (at the start of the tick) to the byte
 * output. If load is off then nothing will happen to the output.
 *
 * @test Constructor, print_out, compute_output and memory_release are tested
 *   in word_memory_test.cpp
 */
class ByteMemory : public byteMicroCircuit<2,1,0,1,11> {
  public:
    /**
     * @brief Constructor sets inputs and implements circuitry.
     * @param load activates the byte output to write the current save value.
     * @param save overwrites the save value with the byte value input
     * @param value the byte value to overwrite with.
     */
    ByteMemory(ptr_t load=ground, ptr_t save=ground, ptr8_t value=ground8);

    /**
     * @brief rewire_input updates the input to ensure the internal circuitry
     *   is conserved if inputs are changed.
     */
    void rewire_input();

    /**
     * @brief memory_release simply releases the delay output.
     */
    void memory_release();

    static const std::string gate_name;
};


/**
 * @brief WordMemory can save an input word for arbitrarily long time.
 * 
 * WordMemory takes a word input to overwrite the save value with; the
 * overwrite occurs if the save bit input is set to one. If load is enabled
 * the gate will write the current value (at the start of the tick) to the word
 * output. If load is off then nothing will happen to the output.
 *
 * @test Constructor, print_out, compute_output and memory_release are tested
 *   in word_memory_test.cpp
 */
class WordMemory : public wordMicroCircuit<2,0,1,0,0,1,35> {
  public:
    /**
     * @brief Constructor sets inputs and implements circuitry.
     * @param load activates the word output to write the current save value.
     * @param save overwrites the save value with the word value input
     * @param value the word value to overwrite with.
     */
    WordMemory(ptr_t load=ground, ptr_t save=ground, ptr32_t value=ground32);

    /**
     * @brief rewire_input updates the input to ensure the internal circuitry
     *   is conserved if inputs are changed.
     */
    void rewire_input();

    /**
     * @brief memory_release simply releases the delay output.
     */
    void memory_release();

    static const std::string gate_name;
};



} //namespace Virtual

#endif
