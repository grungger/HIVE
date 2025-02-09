#include "gate.hpp"
#ifndef SWITCH_IN_H
#define SWITCH_IN_H
namespace Virtual{

class Switch_in : public Gate<0,1> {
  public:
    Switch_in(bool=false);
    static const std::string gate_name;
    void compute_output();
    void change_state(bool);
    
  private:
    bool state_;
};

} //namespace Virtual
#endif
