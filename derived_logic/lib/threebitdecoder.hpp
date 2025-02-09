#include "microcircuit.hpp"
#include "and3.hpp"
#include "onebitdecoder.hpp"
#ifndef THREEBITDECODER_H
#define THREEBITDECODER_H
namespace Virtual{

class ThreeBitDecoder : public microCircuit<3,8,11> {
  public:
    ThreeBitDecoder(ptr_t in1=ground, ptr_t in2=ground, ptr_t in4=ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
