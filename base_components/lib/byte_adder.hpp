#include "bytemicrocircuit.hpp"
#include "full_adder.hpp"
#include "byte_splitter.hpp"
#include "byte_maker.hpp"
#ifndef BYTE_ADDER_H
#define BYTE_ADDER_H
namespace Virtual{

/**
 * ByteAdder takes two bytes and one bit and adds them together into
 * one byte for the sum and a potential carry as a bit.
 */
class ByteAdder : public byteMicroCircuit<1,2,1,1,11> {
  public:
    ByteAdder(ptr_t inbit=ground, ptr8_t sumA=ground8, ptr8_t sumB=ground8);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
