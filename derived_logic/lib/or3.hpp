#include "microcircuit.hpp"
#include "or.hpp"
#ifndef OR3_H
#define OR3_H
namespace Virtual{

class Or3 : public microCircuit<3,1,2> {
  public:
    Or3(ptr_t conA = ground, ptr_t conB = ground, ptr_t conC = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
