#include "bytemicrocircuit.hpp"
#include "byte_splitter.hpp"
#include "byte_maker.hpp"
#include "not.hpp"
#ifndef BYTE_NOT_H
#define BYTE_NOT_H
namespace Virtual{

class ByteNot : public byteMicroCircuit<0,1,0,1,10> {
  public:
    ByteNot(ptr8_t inbyte=ground8);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual
#endif
