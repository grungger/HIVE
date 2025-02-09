#include "microcircuit.hpp"
#include "nand.hpp"
#ifndef NOT_H
#define NOT_H
namespace Virtual{

class Not : public microCircuit<1,1,1> {
  public:
    Not(ptr_t connected = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
