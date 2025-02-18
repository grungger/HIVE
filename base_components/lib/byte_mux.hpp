#include "bytemicrocircuit.hpp"
#include "toggledbyte.hpp"
#include "not.hpp"
#ifndef BYTE_MUX_H
#define BYTE_MUX_H
namespace Virtual{

class ByteMUX : public byteMicroCircuit<1,2,0,1,3> {
  public:
    ByteMUX(ptr_t toggler=ground, ptr32_t inA=ground32, ptr32_t inB=ground32);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
