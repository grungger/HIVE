#include "bytemicrocircuit.hpp"
#ifndef BYTESWITCH_IN_H
#define BYTESWITCH_IN_H
namespace Virtual{

class ByteSwitch_in : public byteMicroCircuit<0,0,0,1,0> {
  public:
    ByteSwitch_in(byte_t);
    ByteSwitch_in(std::uint8_t=0);
    static const std::string gate_name;
    void compute_output();
    void change_state(byte_t);
    void change_state(std::uint8_t);
  private:
    byte_t state_;
};

} //namespace Virtual

#endif
