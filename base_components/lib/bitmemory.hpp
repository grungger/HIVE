#include "bytemicrocircuit.hpp"
#include "delay.hpp"
#include "toggledbit.hpp"
#include "not.hpp"
#ifndef BITMEMORY_H
#define BITMEMORY_H
namespace Virtual{

class BitMemory : public microCircuit<2,1,4> {
  public:
    BitMemory(ptr_t save_enabler=ground, ptr_t save_value=ground);
    void rewire_input();
    static const std::string gate_name;
    void compute_output();
    void memory_release();
};

} //namespace Virtual

#endif
