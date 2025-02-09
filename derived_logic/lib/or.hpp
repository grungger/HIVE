#include "microcircuit.hpp"
#include "nand.hpp"
#include "not.hpp"
#ifndef OR_H
#define OR_H
namespace Virtual{

class Or : public microCircuit<2,1,3> {
  public:
    Or(ptr_t connectedA = ground, ptr_t connectedB = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
