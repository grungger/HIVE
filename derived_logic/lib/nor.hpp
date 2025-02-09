#include "microcircuit.hpp"
#include "nand.hpp"
#include "not.hpp"
#ifndef NOR_H
#define NOR_H
namespace Virtual{

class Nor : public microCircuit<2,1,4> {
  public:
    Nor(ptr_t connectedA = ground, ptr_t connectedB = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
