#include "bytemicrocircuit.hpp"
#include "byte_not.hpp"
#include "byte_adder.hpp"
#ifndef BYTE_NEG_H
#define BYTE_NEG_H
namespace Virtual{

class ByteNeg : public byteMicroCircuit<0,1,0,1,3> {
  public:
    ByteNeg(ptr8_t input = ground8);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
