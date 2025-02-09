#include "gate.hpp"
#ifndef NAND_H
#define NAND_H
namespace Virtual{

class NAND : public Gate<2,1> {
  public:
    NAND(ptr_t connected1 = ground, ptr_t connected2 = ground);
    static const std::string gate_name;
    void compute_output();
};

} //namespace Virtual
#endif
