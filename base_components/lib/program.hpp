#include "bytemicrocircuit.hpp"
#include <cassert>
#ifndef PROGRAM_H
#define PROGRAM_H
namespace Virtual{

class Program : public byteMicroCircuit<0,1,0,4,0> {
  protected:
    std::vector<byte_t> code_lines;
  public:
    Program(ptr8_t locator=ground8);
    template <typename Container>
    void add_lines(const Container& container) {
      assert(container.size() % 4 == 0);
      for(auto it=container.begin(); it<container.end(); it++) {
        code_lines.push_back(*it);
      }
      this->compute_output();
    }
    void edit_code(int location, byte_t replacement);
    void compute_output();
};

} //namespace Virtual

#endif
