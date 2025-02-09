#include "gate.hpp"
#ifndef WIRE_H
#define WIRE_H
namespace Virtual{

class Wire : public Gate<1,1> {
  public:
    Wire(ptr_t input=ground);
    static const std::string gate_name;
    void compute_output();
};

} //namespace Virtual
#endif
