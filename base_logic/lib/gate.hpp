/************************************************************************
 * @file gate.hpp
 * 
 * @brief Implementation of the base template classes BaseGate and Gate.
 ************************************************************************/
// Includes:
#include <array>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <string>

// Header guard:
#ifndef GATE_H
#define GATE_H

namespace Virtual{

// Initialization of byte_t 
// Implementation can be found in base_components/lib/wordmicrocircuit.hpp
struct byte_t;
 
// Initialization of word_t
// Implementation can be found in base_components/lib/wordmicrocircuit.hpp
struct word_t;

// Typename definitions:
/**
 * @brief io_t is the number of inputs or outputs to a gate.
 */
using io_t = unsigned short;
/**
 * @brief ptr_t is the address of a bit
 */
using ptr_t = std::shared_ptr<bool>;
/**
 * @brief ptr8_t is the address of a byte (8 bits)
 */
using ptr8_t = std::shared_ptr<byte_t>;
/**
 * @brief ptr32_t is the address of a word (32 bits)
 */
using ptr32_t = std::shared_ptr<word_t>;


// Initialization and Implementation of ByteArg
/**
 * @brief ByteArg is a struct to quickly interface between 8 bit inputs and a Byte.
 */ 
struct ByteArg {
  /**
   * @brief bits saves each bit in an array with bits[i] corresponding to 2^i.
   */
  std::array<ptr_t, 8> bits;
  
  /**
   * @brief Constructor sets all bits to zero.
   */
  ByteArg() {
    for (int i=0; i<8; i++) {
      bits[i] = std::make_shared<bool>(false);
    }
  }
};

// Initialization and Implementation of WordArg
/**
 * @brief WordArg is a struct to quickly interface between 32 bit inputs and a Word.
 */
struct WordArg {
  /**
   * @brief bits saves each bit in an array with bits[i] corresponding to 2^i.
   */
  std::array<ptr_t,32> bits;

  /**
   * @brief Constructor sets all bits to zero.
   */
  WordArg() {
    for (int i=0; i<32; i++) {
      bits[i] = std::make_shared<bool>(false);
    }
  }
};


/**
 * @brief BaseGate is the ABC base class of all gates.
 * 
 * The BaseGate class is an abstract class modeling all the methods
 * used by the derived classes including Gate, MicroCircuit, byteMicroCircuit.
 * All methods are set to virtual but the ones that only used
 * by selected derived classes have a default implementation.
 */
class BaseGate {
  public:
    virtual ~BaseGate() = default;
    ptr8_t ground8;
    ptr32_t ground32;
    //ptr32_t garbage32;
    virtual void compute_output() = 0;
    const std::string gate_name;
    virtual void print_in() = 0;
    virtual void print_out() = 0;
    virtual void print_components() {}
    virtual void rewire_input() {}
    virtual void init() {}
    virtual void connect_input(ptr_t,io_t) = 0;
    virtual void connect_byte_input(ptr8_t,io_t) {}
    virtual void connect_word_input(ptr32_t,io_t) {}
    virtual ptr_t release_output(io_t) = 0;
    virtual void connect_output(ptr_t) {}
    virtual void connect_byte_output(ptr8_t) {}
    virtual void connect_word_output(ptr32_t) {}
    virtual ptr8_t release_byte_output(io_t) {return this->ground8;}
    virtual ptr32_t release_word_output(io_t) {return this->ground32;}
    virtual ByteArg release_bytearg_output() {return ByteArg();} // {return this->defaultArgb;}
    virtual WordArg release_wordarg_output() {return WordArg();} // {return this->defaultArgw;}
    virtual void memory_release() {}
    virtual void add_lines(std::vector<std::uint8_t>) {}
};

/**
 * @brief Basic implementation of a rudimentary gate processing inputs into outputs.
 * @tparam N_in the number of input connections.
 * @tparam N_out the number of output connections.
 */
template <io_t N_in, io_t N_out>
class Gate : public BaseGate {
  public:
    /** 
     * @brief prints all input bits to std::ostream.
     */
    void print_in() {
      for (auto it=input_pointers_.begin(); it!=input_pointers_.end(); it++) {
        std::cout << *(*(it));
      }
    }

    /**
     * @brief prints all output bits to std::ostream.
     */
    void print_out() {
      for (auto it=output_pointers_.begin(); it!=output_pointers_.end(); it++) {
        std::cout << *(*(it));
      }
    }

    /**
     * @brief Connect the input in input_pointers_[index] to the specified connection.
     * @exception std::domain_error exception thrown in case index is out of range 
     *   of input_pointers_.
     * @param connected_output a pointer to an input bit.
     * @param index the index where the connected_output should be connected.
     */
    void connect_input(ptr_t connected_output, io_t index) {
      if (index >= N_in) {
        throw std::domain_error("Input that was attempted to connect is out of range");
      }
      input_pointers_[index] = connected_output;
    }

    /**
     * @brief Return the pointer to the bit which acts as the (index)th output of self.
     * @exception std::domain_error exception thrown in case index is out of range
     *   of output_pointers_.
     * @param index the index such that the (index)th output pointer is returned.
     * @return output_pointers_[index] the pointer to the output bit.
     */
    ptr_t release_output(io_t index) {
      if (index >= N_out) {
        throw std::domain_error("Input that was attempted to connect is out of range");
      }
      return output_pointers_[index];
    }

    /**
     * @brief ground is a permanent single bit pointer which will always be zero
     */
    static ptr_t ground;

    /**
     * @brief garbage is a permanent single bit pointer that is reserved for unused output.
     */
    static ptr_t garbage;
     
  protected:
    /**
     * @brief input_pointers_ an array of pointers to bits encoding the gate input.
     */
    std::array<ptr_t,N_in> input_pointers_;
    /**
     * @brief output_pointers_ an array of pointers to bits encoding the gate output.
     */
    std::array<ptr_t,N_out> output_pointers_;
};

/**
 * @brief Templated initialization of ground - a static variable of Gate<Nin,Nout>.
 * @tparam N_in number of input bits of the Gate class.
 * @tparam N_out number of output bits of the Gate class.
 */
template <io_t N_in, io_t N_out>
ptr_t Gate<N_in,N_out>::ground = std::make_shared<bool>(false);

/**
 * @brief Templated initilization of garbage - a static variable of Gate<Nin, Nout>.
 * @tparam N_in number of gate input bits.
 * @tparam N_out number of gate output bits.
 */
template <io_t N_in, io_t N_out>
ptr_t Gate<N_in, N_out>::garbage = std::make_shared<bool>(false);

} //namespace Virtual

#endif

