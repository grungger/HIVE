#include "bytemicrocircuit.hpp"
#include "output.hpp"
#include "switch_in.hpp"
#include "byteswitch_in.hpp"
#include "byteoutput.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>
#ifndef CIRCUIT_H
#define CIRCUIT_H
namespace Virtual{

template <io_t Nbit_in, io_t Nbyte_in, io_t Nbit_out, io_t Nbyte_out, io_t N_comp, io_t N_mem>
class Circuit : public byteMicroCircuit<Nbit_in, Nbyte_in, Nbit_out, Nbyte_out, N_comp> {
  protected:
    std::array<std::shared_ptr<Switch_in>, Nbit_in> bit_cin_;
    std::array<std::shared_ptr<ByteSwitch_in>, Nbyte_in> byte_cin_;
    std::array<std::shared_ptr<Output>, Nbit_out> bit_cout_;
    std::array<std::shared_ptr<ByteOutput>, Nbyte_out> byte_cout_; 
    std::array<io_t,N_mem> memory_release_indices_;
  public:
    void connect_couts() {
      for (int i=0; i<Nbit_out; i++) {
        bit_cout_[i]->connect_input(this->output_pointers_[i],0);
      }
      for (int i=0; i<Nbyte_out; i++) {
        byte_cout_[i]->connect_byte_input(this->byte_output_pointers_[i],0);
      }
    }
    
    void print_circuit_out(std::string delimiter=" ") {
      for (int i=0; i<Nbit_out; i++) {
        bit_cout_[i]->compute_output();
        std::cout << delimiter;
      }
      for (int i=0; i<Nbyte_out; i++) {
        byte_cout_[i]->compute_output();
        std::cout << delimiter;
      }
    }
    
    void instantiate_in_out() {
      for (int i=0; i<Nbit_in; i++) {
        bit_cin_[i] = std::make_shared<Switch_in>(false);
      }
      for (int i=0; i<Nbyte_in; i++) {
        byte_cin_[i] = std::make_shared<ByteSwitch_in>(0);
      }
      for (int i=0; i<Nbit_out; i++) {
        bit_cout_[i] = std::make_shared<Output>();
      }
      for (int i=0; i<Nbyte_out; i++) {
        byte_cout_[i] = std::make_shared<ByteOutput>();
      }
    }

    void tick(std::vector<bool> bit_in, std::vector<std::uint8_t> byte_in) {
      for(auto it=memory_release_indices_.begin(); it!=memory_release_indices_.end(); it++) {
        this->circuit_components_[*it]->memory_release();
      }
      if (!bit_in.empty()) {
        int i=0;
        for (auto it=bit_in.begin(); it!=bit_in.end(); it++) {
          if (i==Nbit_in) { throw std::out_of_range("bit input too long"); }
          bit_cin_[i++]->change_state(*it);
        }
        while (i<Nbit_in) {
          bit_cin_[i++]->change_state(bit_in.back());
        }
      }
      if (!byte_in.empty()) {
        int j=0;
        for (auto it=byte_in.begin(); it!= byte_in.end(); it++) {
          if (j==Nbyte_in) { throw std::out_of_range("byte input too long"); }
          byte_cin_[j++]->change_state(*it);
        }
        while (j<Nbyte_in) {
          byte_cin_[j++]->change_state(byte_in.back());
        }
      }
      this->compute_output();
      this->print_circuit_out();
    }

    void run_script(std::vector<std::vector<bool>> bit_ins, std::vector<std::vector<std::uint8_t>> byte_ins) {
      if ((!bit_ins.empty())&&(!byte_ins.empty())&&(bit_ins.size() != byte_ins.size())) {
        throw std::length_error("bits and bytes need to give inputs for the same nr of ticks");
      }
      if (byte_ins.empty()) {
        for (auto it=bit_ins.begin(); it!=bit_ins.end(); it++) {
          tick(*it,std::vector<std::uint8_t>{});
        }
      }
      else if (bit_ins.empty()) {
        for (auto it=byte_ins.begin(); it!=byte_ins.end(); it++) {
          tick(std::vector<bool>{}, *it);
        }
      }
      else {
        auto it2=byte_ins.begin();
        for (auto it=bit_ins.begin(); it!=bit_ins.end(); it++) {
          tick(*it,*(it2++));
        }
      }
    }
};

} //namespace Virtual

#endif



