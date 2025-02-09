#include "bytemicrocircuit.hpp"
#ifndef BYTE_MAKER_H
#define BYTE_MAKER_H
namespace Virtual{

struct ByteArg {
  ptr_t in1 = Gate<0,0>::ground;
  ptr_t in2 = Gate<0,0>::ground;
  ptr_t in3 = Gate<0,0>::ground;
  ptr_t in4 = Gate<0,0>::ground;
  ptr_t in5 = Gate<0,0>::ground;
  ptr_t in6 = Gate<0,0>::ground;
  ptr_t in7 = Gate<0,0>::ground;
  ptr_t in8 = Gate<0,0>::ground;
};

class ByteMaker : public byteMicroCircuit<8,0,0,1,0> {
  public:
    ByteMaker(ptr_t in1=ground, ptr_t in2=ground, ptr_t in3=ground, ptr_t in4=ground, ptr_t in5=ground, ptr_t in6=ground, ptr_t in7=ground, ptr_t in8=ground);
    ByteMaker(ByteArg& args);
    void compute_output();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
