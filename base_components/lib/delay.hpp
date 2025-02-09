#include "gate.hpp"
#ifndef DELAY_H
#define DELAY_H
namespace Virtual{

class Delay : public Gate<1,1> {
  public:
    Delay(ptr_t connect = ground);
    static const std::string gate_name;
    void compute_output();
    void memory_release();
  private:
    bool save_;
};

} //namespace Virtual

#endif
