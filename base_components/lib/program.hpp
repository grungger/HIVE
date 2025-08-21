/*******************************************
 * @file program.hpp
 *
 * @brief Implementation of ByteProgram and Program.
 *******************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include <stdexcept>

// Header Guards:
#ifndef PROGRAM_H
#define PROGRAM_H

namespace Virtual{

/**
 * @brief ByteProgram saves 8bit instructions to test the computer architecture.
 *
 * ByteProgram saves lines of code in the form of a list of bytes and outputs
 * one byte at a time, corresponding to the location given by the input
 * (the input is usually connected to a counter, in order to walk through
 * the program).
 */
class ByteProgram : public byteMicroCircuit<0,1,0,1,0> {
  protected:
    /**
     * @brief code_lines saves the instruction bytes.
     */
    std::vector<byte_t> code_lines;

  public:
    /**
     * @brief Constructor for the ByteProgram block.
     * @param locator is an input byte that tells the program which instruction to execute.
     */
    ByteProgram(ptr8_t locator=ground8);

    /**
     * @brief add_lines is a function to add code bytes.
     * @param container the new code lines to be added.
     */
    void add_lines(const std::vector<std::uint8_t>& container) {
      for(auto it=container.begin(); it<container.end(); it++) {
        code_lines.push_back(*it);
      }
      this->compute_output();
    }

    /**
     * @brief edit_code allows for changing a specific code byte.
     * @param location the index of the byte to be replaced.
     * @param replacement the new byte to overwrite with.
     * @throws std::domain_error if location is out of range.
     */
    void edit_code(int location, byte_t replacement);

    /**
     * @brief Writes the code line at location given by input to output.
     * @throws std::domain_error if input value is out of range of code_lines.
     */
    void compute_output();
};


/**
 * @brief Program saves word instructions to test the computer architecture.
 *
 * Program saves lines of code in the form of a list of 32bit words and outputs
 * one word at a time, corresponding to the location given by the input
 * (the input is usually connected to a counter, in order to walk through
 * the program).
 */
class Program : public wordMicroCircuit<0,1,1,0,0,1,0> {
  protected:
    /**
     * @brief code_lines saves the instruction words.
     */
    std::vector<word_t> code_lines;

    /**
     * @brief byte_word_bool toggles the Program to either read code addresses
     *   from a byte (byte_word_bool = False) or from a word (byte_word_bool = True)
     *   which allows for longer code_lines to be accessible.
     */
     bool byte_word_bool;

  public:
    /**
     * @brief Constructor for Program block with byte input; sets byte_word_bool False.
     * @param locator is an input byte that tells the program which instruction to execute.
     */
    Program(ptr8_t locator=ground8);

    /**
     * @brief Constructor for Program block with word input; sets byte_word_bool True.
     * @param locator is an input word that tells the program which instruction to execute.
     */
    Program(ptr32_t locator=ground32);

    /**
     * @brief add_lines is a templated function to add code words.
     * @tparam Container is any iterable container containing word_t values.
     * @param container the new code lines to be added.
     */
    template <typename Container>
    void add_lines(const Container& container) {
      for(auto it=container.begin(); it<container.end(); it++) {
        code_lines.push_back(*it);
      }
      this->compute_output();
    }

    /**
     * @brief edit_code allows for changing a specific code word.
     * @param location the index of the word to be replaced.
     * @param replacement the new word to overwrite with.
     * @throws std::domain_error if location is out of range.
     */
    void edit_code(int location, word_t replacement);

    /**
     * @brief Writes the code line at location given by input to output.
     * @throws std::domain_error if input value is out of range of code_lines.
     */
    void compute_output();
};

} //namespace Virtual

#endif
