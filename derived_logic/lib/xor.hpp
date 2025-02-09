#include "microcircuit.hpp"
#include "nor.hpp"
#include "and.hpp"
#ifndef XOR_H
#define XOR_H
namespace Virtual{

class Xor : public microCircuit<2,1,3> {
  public:
    Xor(ptr_t connectedA = ground, ptr_t connectedB = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
