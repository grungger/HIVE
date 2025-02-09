#include "bytemicrocircuit.hpp"
#include "byte_splitter.hpp"
#include "byte_maker.hpp"
#include "or.hpp"
#ifndef BYTE_OR_H
#define BYTE_OR_H
namespace Virtual{

class ByteOr : public byteMicroCircuit<0,2,0,1,11> {
  public:
    ByteOr(ptr8_t inA=ground8, ptr8_t inB=ground8);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
