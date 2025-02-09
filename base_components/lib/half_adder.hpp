#include "microcircuit.hpp"
#include "xor.hpp"
#include "and.hpp"
#ifndef HALF_ADDER_H
#define HALF_ADDER_H
namespace Virtual{

class HalfAdder : public microCircuit<2,2,2> {
  public:
    HalfAdder(ptr_t conA = ground, ptr_t conB = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual;

#endif
