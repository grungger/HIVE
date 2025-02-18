#include "bytemicrocircuit.hpp"
#ifndef BYTE_SPLITTER_H
#define BYTE_SPLITTER_H
namespace Virtual{

class ByteSplitter : public byteMicroCircuit<0,1,8,0,0> {
  public:
    ByteSplitter(ptr32_t conA = ground32);
    void compute_output();
    static const std::string gate_name;
};

} //namespace Virtual

#endif

