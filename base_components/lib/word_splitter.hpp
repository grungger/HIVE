/********************************************
 * @file word_splitter.hpp
 * 
 * @brief Implementation of ByteSplitter and WordSplitter splitting them into bits.
 ********************************************/
// Includes:
#include "wordmicrocircuit.hpp"

// Header Guards:
#ifndef WORD_SPLITTER_H
#define WORD_SPLITTER_H

namespace Virtual{

/**
 * @brief ByteSplitter takes a byte_t and splits it into its 8 bits.
 * 
 * ByteSplitter takes one byte input and writes the 2^i component of the byte
 * to the output at index i, i.e. the outputs have ascending order 2^i.
 */
class ByteSplitter : public byteMicroCircuit<0,1,8,0,0> {
  public:
    /**
     * @brief Constructor sets input and creates outputs.
     * @note ByteSplitter makes use of the indexing of byte_t to access ith bit.
     * @param conA the input byte.
     */
    ByteSplitter(ptr8_t conA = ground8);
    
    /**
     * @brief compute_output writes the 2^i splitting of input byte to output bits.
     */
    void compute_output();

    /**
     * @brief release_bytearg_output is a custom version of release_output,
     *   releasing all bit outputs at the same time with a ByteArg object.
     * @return ByteArg containing all bit outputs of ByteSplitter.
     */
    ByteArg release_bytearg_output();

    static const std::string gate_name;
};


/**
 * @brief WordSplitter takes word_t and splits it into its 32 bits.
 *
 * WordSplitter takes one word input and writes the 2^i component of the word
 * to the output at index i, i.e. the outputs have ascending order 2^i.
 */
class WordSplitter : public wordMicroCircuit<0,0,1,32,0,0,0> {
  public:
    /**
     * @brief Constructor sets input and creates outputs.
     * @note WordSplitter makes use of index overloading for word_t.
     * @param conA the input word.
     */
    WordSplitter(ptr32_t conA = ground32);
    
    /**
     * @brief compute_output writes the 2^i splitting of input word to output bits.
     */
    void compute_output();
    
    /**
     * @brief release_wordarg_output is a custom version of release_output, releasing
     *   all bit outputs via one WordArg instance.
     * @return WordArg containing all bit outputs of WordSplitter.
     */
    WordArg release_wordarg_output();


    static const std::string gate_name;
};

} //namespace Virtual

#endif

