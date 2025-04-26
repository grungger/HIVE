/*****************************
 * @file circuit.hpp
 *
 * @brief Implementation of Circuit to encapsulate a circuit of components.
 ****************************/

#include "wordmicrocircuit.hpp"
#include "output.hpp"
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include "word_output.hpp"
#include <array>
#include <vector>
#include <cassert>

#ifndef CIRCUIT_H
#define CIRCUIT_H

namespace Virtual{


/**
 * @brief Circuit embeds input gates and output gates together
 *   with any arbitrary circuitry into a large circuit.
 * @tparam Nbit_in number of Switch_in input bits.
 * @tparam Nbyte_in number of ByteSwitch_in input bytes.
 * @tparam Nword_in number of WordSwitch_in input words.
 * @tparam Nbit_out number of Output bits.
 * @tparam Nbyte_out number of ByteOutput's.
 * @tparam Nword_out number of WordOutput's.
 */
template <io_t Nbit_in, io_t Nbyte_in, io_t Nword_in, 
	io_t Nbit_out, io_t Nbyte_out, io_t Nword_out>
class Circuit {
  protected:
    std::array<std::shared_ptr<Switch_in>, Nbit_in> bit_cin_;
    std::array<std::shared_ptr<ByteSwitch_in>, Nbyte_in> byte_cin_;
    std::array<std::shared_ptr<WordSwitch_in>, Nword_in> word_cin_;
    std::array<std::shared_ptr<Output>, Nbit_out> bit_cout_;
    std::array<std::shared_ptr<ByteOutput>, Nbyte_out> byte_cout_;
    std::array<std::shared_ptr<WordOutput>, Nword_out> word_cout_;
    std::vector<std::shared_ptr<BaseGate>> components_;
    std::vector<std::shared_ptr<BaseGate>> memory_components_;
  public:
    /**
     * @brief init initializes all the input and output gates.
     */
    void init() {
      for (int i=0; i<Nbit_in; i++) {
        bit_cin_[i] = std::make_shared<Switch_in>(false);
      }
      for (int i=0; i<Nbyte_in; i++) {
        byte_cin_[i] = std::make_shared<ByteSwitch_in>(0);
      }
      for (int i=0; i<Nword_in; i++) {
        word_cin_[i] = std::make_shared<WordSwitch_in>(0);
      }
      for (int i=0; i<Nbit_out; i++) {
        bit_cout_[i] = std::make_shared<Output>();
      }
      for (int i=0; i<Nbyte_out; i++) {
        byte_cout_[i] = std::make_shared<ByteOutput>();
      }
      for (int i=0; i<Nword_out; i++) {
        word_cout_[i] = std::make_shared<WordOutput>();
      }
    }

    /**
     * @brief tick runs all circuit components in sequence and runs
     *   compute_output on the output gates.
     */
    void tick(	std::vector<bool> bit_in,
		std::vector<std::uint8_t> byte_in,
		std::vector<std::uint32_t> word_in) {
      for (auto it=memory_components_.begin(); it!=memory_components_.end(); it++) {
        (*it)->memory_release();
      }
      assert(bit_in.size()<=(this->bit_cin_).size());
      auto bit_it = bit_cin_.begin();
      for (auto it=bit_in.begin(); it!=bit_in.end(); it++) {
        (*bit_it)->change_state(*it);
        bit_it++;
      }
      assert(byte_in.size()<=(this->byte_cin_).size());
      auto byte_it = byte_cin_.begin();
      for (auto it=byte_in.begin(); it!=byte_in.end(); it++) {
        (*byte_it)->change_state(*it);
        byte_it++;
      }
      assert(word_in.size()<=(this->word_cin_).size());
      auto word_it = word_cin_.begin();
      for (auto it=word_in.begin();it!=word_in.end(); it++) {
        (*word_it)->change_state(*it);
        word_it++;
      }
      // Run all components:
      for (auto it=components_.begin(); it!=components_.end(); it++) {
        (*it)->compute_output();
      }
      // Print outputs:
      for (auto it=bit_cout_.begin(); it!=bit_cout_.end(); it++) {
        (*it)->compute_output();
      }
      for (auto it=byte_cout_.begin(); it!=byte_cout_.end(); it++) {
        (*it)->compute_output();
      }
      for (auto it=word_cout_.begin(); it!=word_cout_.end(); it++) {
        (*it)->compute_output();
      }
    }

    void tick(std::vector<bool> bit_in) {
      for (auto it=memory_components_.begin(); it!=memory_components_.end(); it++) {
        (*it)->memory_release();
      }
      assert(bit_in.size()<=(this->bit_cin_).size());
      auto bit_it = bit_cin_.begin();
      for (auto it=bit_in.begin(); it!=bit_in.end(); it++) {
        (*bit_it)->change_state(*it);
        bit_it++;
      }
      // Run all components:
      for (auto it=components_.begin(); it!=components_.end(); it++) {
        (*it)->compute_output();
      }
      // Print outputs:
      for (auto it=bit_cout_.begin(); it!=bit_cout_.end(); it++) {
        (*it)->compute_output();
      }
      for (auto it=byte_cout_.begin(); it!=byte_cout_.end(); it++) {
        std::cout << 'b';
        (*it)->compute_output();
      }
      for (auto it=word_cout_.begin(); it!=word_cout_.end(); it++) {
        std::cout << 'w';
        (*it)->compute_output();
      }
      std::cout << ' ';
    }

    void tick(std::vector<std::uint8_t> byte_in) {
      for (auto it=memory_components_.begin(); it!=memory_components_.end(); it++) {
        (*it)->memory_release();
      }
      assert(byte_in.size()<=(this->byte_cin_).size());
      auto byte_it = byte_cin_.begin();
      for (auto it=byte_in.begin(); it!=byte_in.end(); it++) {
        (*byte_it)->change_state(*it);
        byte_it++;
      }
      // Run all components:
      for (auto it=components_.begin(); it!=components_.end(); it++) {
        (*it)->compute_output();
      }
      // Print outputs:
      for (auto it=bit_cout_.begin(); it!=bit_cout_.end(); it++) {
        (*it)->compute_output();
      }
      for (auto it=byte_cout_.begin(); it!=byte_cout_.end(); it++) {
        std::cout << 'b';
        (*it)->compute_output();
      }
      for (auto it=word_cout_.begin(); it!=word_cout_.end(); it++) {
        std::cout << 'w';
        (*it)->compute_output();
      }
      std::cout << ' ';
    }

    void tick(std::vector<std::uint32_t> word_in) {
      for (auto it=memory_components_.begin(); it!=memory_components_.end(); it++) {
        (*it)->memory_release();
      }
      assert(word_in.size()<=(this->word_cin_).size());
      auto word_it = word_cin_.begin();
      for (auto it=word_in.begin(); it!=word_in.end(); it++) {
        (*word_it)->change_state(*it);
        word_it++;
      }
      // Run all components:
      for (auto it=components_.begin(); it!=components_.end(); it++) {
        (*it)->compute_output();
      }
      // Print outputs:
      for (auto it=bit_cout_.begin(); it!=bit_cout_.end(); it++) {
        (*it)->compute_output();
      }
      for (auto it=byte_cout_.begin(); it!=byte_cout_.end(); it++) {
        std::cout << 'b';
        (*it)->compute_output();
      }
      for (auto it=word_cout_.begin(); it!=word_cout_.end(); it++) {
        std::cout << 'w';
        (*it)->compute_output();
      }
      std::cout << ' ';
    }


};

} // namespace Virtual  

#endif     
