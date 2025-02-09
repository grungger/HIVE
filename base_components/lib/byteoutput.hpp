#include "bytemicrocircuit.hpp"
#ifndef BYTEOUTPUT_H
#define BYTEOUTPUT_H
namespace Virtual{

class ByteOutput : public byteMicroCircuit<0,1,0,0,0> {
  public:
    ByteOutput(ptr8_t connector=ground8);
    static const std::string gate_name;
    void compute_output();
    void printf_out();
  private:
    static int counter_;
    const int id_;
};

} //namespace Virtual

#endif
