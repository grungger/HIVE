#include "microcircuit.hpp"
#include "or.hpp"
#include "half_adder.hpp"
#ifndef FULL_ADDER_H
#define FULL_ADDER_H
namespace Virtual{

class FullAdder : public microCircuit<3,2,3> {
  public:
    FullAdder(ptr_t conA = ground, ptr_t conB = ground, ptr_t conC = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
