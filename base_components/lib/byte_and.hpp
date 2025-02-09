#include "bytemicrocircuit.hpp"
#include "byte_splitter.hpp"
#include "byte_maker.hpp"
#include "and.hpp"
#ifndef BYTE_AND_H
#define BYTE_AND_H
namespace Virtual{

class ByteAnd : public byteMicroCircuit<0,2,0,1,11> {
  public:
    ByteAnd(ptr8_t inA=ground8, ptr8_t inB=ground8);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
