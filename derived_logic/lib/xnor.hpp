#include "microcircuit.hpp"
#include "xor.hpp"
#include "not.hpp"
#ifndef XNOR_H
#define XNOR_H
namespace Virtual{

class Xnor : public microCircuit<2,1,2> {
  public:
    Xnor(ptr_t connectedA = ground, ptr_t connectedB = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
