#include <array>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <string>
#ifndef GATE_H
#define GATE_H
namespace Virtual{
using io_t = unsigned short;
using ptr_t = std::shared_ptr<bool>;
struct byte_t;
using ptr8_t = std::shared_ptr<byte_t>;

class BaseGate {
  public:
    virtual ~BaseGate() = default;
    ptr8_t ground8;
    virtual void compute_output() = 0;
    const std::string gate_name;
    virtual void print_in() = 0;
    virtual void print_out() = 0;
    virtual void print_components() {}
    virtual void rewire_inputs() {}
    virtual void connect_input(ptr_t,io_t) = 0;
    virtual void connect_byte_input(ptr8_t,io_t) {}
    virtual ptr_t release_output(io_t) = 0;
    virtual void connect_output(ptr_t) {}
    virtual void connect_byte_output(ptr8_t) {}
    virtual ptr8_t release_byte_output(io_t) {return this->ground8;}
    virtual void memory_release() {}
};

template <io_t N_in, io_t N_out>
class Gate : public BaseGate {
  public:
    void print_in() {
      for (auto it=input_pointers_.begin(); it!=input_pointers_.end(); it++) {
        std::cout << *(*(it));
      }
    }
    void print_out() {
      for (auto it=output_pointers_.begin(); it!=output_pointers_.end(); it++) {
        std::cout << *(*(it));
      }
    }
    void connect_input(ptr_t connected_output, io_t index) {
      if (index >= N_in) {
        throw std::domain_error("Input that was attempted to connect is out of range");
      }
      input_pointers_[index] = connected_output;
    }
    ptr_t release_output(io_t index) {
      if (index >= N_out) {
        throw std::domain_error("Input that was attempted to connect is out of range");
      }
      return output_pointers_[index];
    }
    static ptr_t ground;
     
  protected:
    std::array<ptr_t,N_in> input_pointers_;
    std::array<ptr_t,N_out> output_pointers_;
};

template <io_t N_in, io_t N_out>
ptr_t Gate<N_in,N_out>::ground = std::make_shared<bool>(false);

} //namespace Virtual
#endif
