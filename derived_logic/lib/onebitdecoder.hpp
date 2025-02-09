#include "microcircuit.hpp"
#include "wire.hpp"
#include "not.hpp"
#ifndef ONEBITDECODER_H
#define ONEBITDECODER_H
namespace Virtual{

class OneBitDecoder : public microCircuit<1,2,2> {
  public:
    OneBitDecoder(ptr_t input=ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
