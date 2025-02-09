#include "bytemicrocircuit.hpp"
#include "byte_splitter.hpp"
#include "byte_maker.hpp"
#include "nand.hpp"
#ifndef BYTE_NAND_H
#define BYTE_NAND_H
namespace Virtual{

class ByteNAND : public byteMicroCircuit<0,2,0,1,11> {
  public:
    ByteNAND(ptr8_t inA=ground8, ptr8_t inB=ground8);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
