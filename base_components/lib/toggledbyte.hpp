#include "bytemicrocircuit.hpp"
#ifndef TOGGLEDBYTE_H
#define TOGGLEDBYTE_H
namespace Virtual{

class ToggledByte : public byteMicroCircuit<1,1,0,1,0> {
  public:
    ToggledByte(ptr32_t input=ground32, ptr_t toggle=ground);
    static const std::string gate_name;
    void compute_output();
    void connect_byte_output(ptr32_t connected_output);
};

} //namespace Virtual

#endif
