#include "bytemicrocircuit.hpp"
#include "bitmemory.hpp"
#include "byte_splitter.hpp"
#include "byte_maker.hpp"
#include "toggledbyte.hpp"
#ifndef BYTEMEMORY_H
#define BYTEMEMORY_H
namespace Virtual{

class ByteMemory : public byteMicroCircuit<2,1,0,1,11> {
  public:
    ByteMemory(ptr_t load=ground, ptr_t save=ground, ptr8_t value=ground8);
    void rewire_input();
    void memory_release();
    static const std::string gate_name;
};

} //namespace Virtual

#endif
