#include "microcircuit.hpp"
#include "nand.hpp"
#include "not.hpp"
#ifndef AND_H
#define AND_H
namespace Virtual{

class And : public microCircuit<2,1,2> {
  public:
    And(ptr_t connectedA = ground, ptr_t connectedB = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
