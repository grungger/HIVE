#include <iostream>
#include "gate.hpp"
#ifndef OUTPUT_H
#define OUTPUT_H
namespace Virtual{

class Output : public Gate<1,0> {
  public:
    Output(ptr_t connected = ground);
    static const std::string gate_name;
    void compute_output();
    void printf_out();
  
  private:
    static int counter_;
    const int id_;
};

} //namespace Virtual

#endif
