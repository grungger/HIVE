/*******************************************
 * @file word_maker.hpp
 *
 * @brief Implementation of ByteMaker and WordMaker to convert 8 or 32 bits
 *   into a byte or word type.
 *******************************************/
// Includes:
#include "wordmicrocircuit.hpp"

// Header Guards:
#ifndef WORD_MAKER_H
#define WORD_MAKER_H

namespace Virtual{

/**
 * @brief ByteMaker converts 8 bit inputs into one byte output.
 * 
 * ByteMaker takes 8 bit input pointers and interprets as ascending order of bit value
 * i.e. the i-th input is interpreted as 2^i, where all inputs are summed into a
 * byte_t output with the sum as value member.
 */
class ByteMaker : public byteMicroCircuit<8,0,0,1,0> {
  public:
    /**
     * @brief Constructor sets all input bits and converts to a byte number
     *   representation, by using bitwise or and bitshift.
     * @param in1 lowest order input bit 2^0
     * @param in2 2nd input bit 2^1
     * @param in4 3rd input bit 2^2
     * @param in8 4th input bit 2^3
     * @param in16 5th input bit 2^4
     * @param in32 6th input bit 2^5
     * @param in64 7th input bit 2^6
     * @param in128 8th input bit 2^7
     */
    ByteMaker(ptr_t in1=ground, ptr_t in2=ground, 
              ptr_t in4=ground, ptr_t in8=ground, 
              ptr_t in16=ground, ptr_t in32=ground, 
              ptr_t in64=ground, ptr_t in128=ground);
    
    /**
     * @brief Constructor from custom input class ByteArg analogous to default ctor.
     * @param args is a ByteArg object that summarizes all default ctor arguments.
     */
    ByteMaker(ByteArg args);

    /**
     * @brief compute_output computes the byte integer representation of the input bits.
     */
    void compute_output();

    static const std::string gate_name;
};


/**
 * @brief WordMaker takes 32 bits of input and converts them to a word.
 *
 * WordMaker takes 32 bits of input either individually or in the form of 4 ByteArgs.
 * It converts the inputs into a single word output, analoguous to ByteMaker.
 */
class WordMaker : public wordMicroCircuit<32,0,0,0,0,1,0> {
  public:
    /**
     * @brief Constructor sets all 32 input bits and converts them to a word value.
     * @param in{j} is the jth input bit.
     */
    WordMaker(ptr_t in1=ground, ptr_t in2=ground, ptr_t in3=ground, ptr_t in4=ground,
              ptr_t in5=ground, ptr_t in6=ground, ptr_t in7=ground, ptr_t in8=ground,
              ptr_t in9=ground, ptr_t in10=ground, ptr_t in11=ground, ptr_t in12=ground,
              ptr_t in13=ground, ptr_t in14=ground, ptr_t in15=ground, ptr_t in16=ground,
              ptr_t in17=ground, ptr_t in18=ground, ptr_t in19=ground, ptr_t in20=ground,
              ptr_t in21=ground, ptr_t in22=ground, ptr_t in23=ground, ptr_t in24=ground,
              ptr_t in25=ground, ptr_t in26=ground, ptr_t in27=ground, ptr_t in28=ground,
              ptr_t in29=ground, ptr_t in30=ground, ptr_t in31=ground, ptr_t in32=ground);

    /**
     * @brief Constructor from custom input class ByteArg analagous to default ctor.
     * @param arg{j} jth input byte wrapped in a ByteArg.
     */
    WordMaker(ByteArg arg1, ByteArg arg2, ByteArg arg3, ByteArg arg4);

    /**
     * @brief Constructor from custom input class WordArg analagous to default ctor.
     * @param arg the input word wrapped in a WordArg.
     */
    WordMaker(WordArg arg);
    
    /**
     * @brief compute_output converts the 32 bit input into the std::uint32_t value word.
     */
    void compute_output();

    static const std::string gate_name;
};


/**
 * @brief WordMakerByte takes 4 bytes of input and converts them to a word.
 */
class WordMakerByte : public wordMicroCircuit<0,4,0,0,0,1,0> {
  public:
    /**
     * @brief Constructor sets all 4 input bytes and converts them to a word value.
     * @param in{j} is the jth input byte.
     */
    WordMakerByte(ptr8_t in1=ground8, ptr8_t in2=ground8, ptr8_t in3=ground8, ptr8_t=ground8);

    /**
     * @brief compute_output converts the 4 byte input into the std::uint32_t value word.
     */
    void compute_output();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
