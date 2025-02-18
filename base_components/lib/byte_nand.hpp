#include "bytemicrocircuit.hpp"
#include "byte_splitter.hpp"
#include "byte_maker.hpp"
#include "nand.hpp"
#ifndef BYTE_NAND_H
#define BYTE_NAND_H
namespace Virtual{

class ByteNAND : public byteMicroCircuit<0,2,0,1,11> {
  public:
    ByteNAND(ptr32_t inA=ground32, ptr32_t inB=ground32);
    void rewire_input();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
