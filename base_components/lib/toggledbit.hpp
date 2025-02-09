#include "gate.hpp"
#ifndef TOGGLEDBIT_H
#define TOGGLEDBIT_H
namespace Virtual{

class ToggledBit : public Gate<2,1>  {
  public:
    ToggledBit(ptr_t conIn=ground, ptr_t conTog=ground);
    static const std::string gate_name;
    void compute_output();
    void connect_output(ptr_t connected_output);
};

} //namespace Virtual

#endif
