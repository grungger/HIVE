#include "microcircuit.hpp"
#include "and.hpp"
#ifndef AND3_H
#define AND3_H
namespace Virtual{

class And3 : public microCircuit<3,1,2> {
  public:
    And3(ptr_t conA = ground, ptr_t conB = ground, ptr_t conC = ground);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
