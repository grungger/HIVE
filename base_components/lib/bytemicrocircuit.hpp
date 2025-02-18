#include "microcircuit.hpp"
#include <cstdint>
#include <iostream>
#include <cassert>
#ifndef BYTEMICROCIRCUIT_H
#define BYTEMICROCIRCUIT_H
namespace Virtual{

struct byte_t {
  std::uint8_t value;

  template <typename T>
  byte_t(T num_tval) : value(static_cast<std::uint8_t>(num_tval)) {}
  
  byte_t(const byte_t &rhs) : value(rhs.value) {}

  bool operator[](int i) {
    assert((i>=0 && i<8));
    std::uint8_t mask = 1 << i;
    return (value&mask) == mask;
  }
  
  byte_t operator+(const byte_t& rhs) {
    byte_t new_byt(this->value + rhs.value);
    return new_byt;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const byte_t& obj) {
    os << static_cast<int>(obj.value);
    return os;
  }
  
  byte_t& operator=(const byte_t& rhs) {
    this->value = rhs.value;
    return *this;
  } 
};

using ptr32_t = std::shared_ptr<byte_t>;

template <io_t Nbit_in, io_t Nbyte_in, io_t Nbit_out, io_t Nbyte_out, io_t N_comp>
class byteMicroCircuit : public microCircuit<Nbit_in, Nbit_out, N_comp> {
  protected:
    std::array<ptr32_t, Nbyte_in> byte_input_pointers_;
    std::array<ptr32_t, Nbyte_out> byte_output_pointers_;
  public:
    static ptr32_t ground32;
    
    void print_in() {
      for (auto it=this->input_pointers_.begin(); it!=this->input_pointers_.end(); it++) {
        std::cout << *(*it);
      }
      std::cout << std::endl;
      for (auto it=byte_input_pointers_.begin(); it!=byte_input_pointers_.end();it++) {
        std::cout << static_cast<int>((*it)->value);
      }
    }

    void print_out() {
      for (auto it=this->output_pointers_.begin(); it!=this->output_pointers_.end(); it++) {
        std::cout << *(*it);
      }
      std::cout << std::endl;
      for (auto it=byte_output_pointers_.begin();it!=byte_output_pointers_.end();it++) {
         std::cout << static_cast<int>((*it)->value);
      }
    }

    virtual void rewire_input() {};      

    void connect_byte_input(ptr32_t connected8, io_t index) {
      if (index >= Nbyte_in) {
        throw std::domain_error("Input that was attempted to connect is out of range");
      }
      byte_input_pointers_[index] = connected8;
      rewire_input();
    }

    ptr32_t release_byte_output(io_t index) {
      if (index >= Nbyte_out) {
        throw std::domain_error("Output tried to release is out of range");
      }
      return byte_output_pointers_[index];
    }
};

template <io_t Nbit_in, io_t Nbyte_in, io_t Nbit_out, io_t Nbyte_out, io_t N_comp>
ptr32_t byteMicroCircuit<Nbit_in,Nbyte_in,Nbit_out,Nbyte_out,N_comp>::ground32 = std::make_shared<byte_t>(0);

} //namespace Virtual

#endif
