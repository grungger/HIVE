/**********************************
 * @file register_plus.hpp
 *
 * @brief Implementation of RegisterPlus.
 **********************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_memory.hpp"
#include "not.hpp"
#include "toggledword.hpp"

// Header Guards:
#ifndef REGISTER_PLUS_H
#define REGISTER_PLUS_H

namespace Virtual{

/**
 * @brief RegisterPlus can save an input byte for arbitrarily long time.
 */
class RegisterPlus : public byteMicroCircuit<2,1,0,2,3> {
  public:
    /**
     * @brief Constructor sets inputs and implements circuitry.
     * @param load activates the byte output to write the current save value.
     * @param save overwrites the save value with the byte value input
     * @param value the byte value to overwrite with.
     */
    RegisterPlus(ptr_t load=ground, ptr_t save=ground, ptr8_t value=ground8);

    /**
     * @brief rewire_input updates the input to ensure the internal circuitry
     *   is conserved if inputs are changed.
     */
    void rewire_input();

    /**
     * @brief memory_release simply releases the delay output.
     */
    void memory_release();

    /**
     * @brief connect_byte_output reroutes the toggledbyte method to the outer shell.
     */
    void connect_byte_output(ptr8_t conOut);

    static const std::string gate_name;
};

/**
 * @brief RegisterMax can save an input word for arbitrarily long time.
 */
class RegisterMax : public wordMicroCircuit<2,0,1,0,0,2,3> {
  public:
    /**
     * @brief Constructor sets inputs and implements circuitry.
     * @param load activates the word output to write the current save value.
     * @param save overwrites the save value with the word value input
     * @param value the word value to overwrite with.
     */
    RegisterMax(ptr_t load=ground, ptr_t save=ground, ptr32_t value=ground32);

    /**
     * @brief rewire_input updates the input to ensure the internal circuitry
     *   is conserved if inputs are changed.
     */
    void rewire_input();

    /**
     * @brief memory_release simply releases the delay output.
     */
    void memory_release();

    /**
     * @brief connect_word_output reroutes the toggledWord method to the outer shell.
     */
    void connect_word_output(ptr32_t conOut);

    static const std::string gate_name;
};


} //namespace Virtual

#endif
