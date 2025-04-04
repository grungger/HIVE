/****************************************************
 * @file wordmicrocircuit.hpp
 *
 * @brief Implementation of a byte representation and a 32bit-word representation,
 *   as well as the wordMicroCircuit class which takes 32bit-words as input on top
 *   of normal bit inputs making it a natural extension to the microCircuit class.
 *****************************************************/
// Includes:
#include "microcircuit.hpp"
#include <iostream>
#include <cassert>

// Header Guards:
#ifndef WORDMICROCIRCUIT_H
#define WORDMICROCIRCUIT_H

namespace Virtual{

/**
 * @brief byte_t is a type that represents a byte of data (or 8 bits).
 * 
 * byte_t saves one byte using the std::uint8_t type as a member variable
 * of the byte_t struct and allows for initialization with integer types
 * small enough to be convertible to std::uint8_t. It also has methods
 * for accessing individual bits via operator[].
 */ 
struct byte_t {
  /**
   * @brief value is the member variable that holds the bit values.
   */
  std::uint8_t value;

  /**
   * @brief Templated constructor for a byte_t using a numeric type that
   *   is convertible to std::uint8_t.
   * @tparam T any numeric type convertible to std::uint8_t.
   */
  template <typename T, 
	typename = typename std::enable_if<std::is_convertible<T, 
						std::uint8_t>::value>::type>
  byte_t(T num_tval) : value(static_cast<std::uint8_t>(num_tval)) {}
  
  /**
   * @brief Copy constructor simply copies the value of the argument.
   */
  byte_t(const byte_t &rhs) : value(rhs.value) {}

  /**
   * @brief Overloading the subscript operator for direct access to
   *   the individual bits.
   * @param i to access i-th bit (of i-th order).
   * @exception assert statement to ensure index i is not out of range (8 bits).
   */
  bool operator[](int i) {
    assert((i>=0 && i<8));
    std::uint8_t mask = 1 << i; // mask with a 1 in the bit i and 0 elsewhere
    return (value&mask) == mask; // bitwise And on std::uint8_t to isolate bit i
  }
  
  byte_t operator+(const byte_t& rhs) {
    byte_t new_byt(this->value + rhs.value);
    return new_byt;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const byte_t& obj) {
    os << static_cast<unsigned int>(obj.value);
    return os;
  }
  
  byte_t& operator=(const byte_t& rhs) {
    this->value = rhs.value;
    return *this;
  } 
};


/**
 * @brief word_t is a type representing 32 bits of data i.e. 4 bytes.
 *
 * word_t saves 4 bytes of data using the std::uint32_t type as a member
 * variable, the bits can be accessed via operator[].
 */
struct word_t {
  /**
   * @brief value is the member variable saving the word.
   */
  std::uint32_t value;
  
  /**
   * @brief Templated constructor for a word_t using a numeric type.
   * @tparam T any numeric type convertible to std::uint32_t.
   */
  template <typename T,
	typename = typename std::enable_if<std::is_convertible<T,
					std::uint32_t>::value>::type>
  word_t(T num_tval) : value(static_cast<std::uint32_t>(num_tval)) {}
  
  /**
   * @brief Copy constructor simply copies the value of the argument.
   */
  word_t(const word_t &rhs) : value(rhs.value) {}
  
  /**
   * @brief Overloading the subscript operator to access the individual bits.
   * @param i to access i-th bit (of order 2^i)
   * @exception assert statement to ensure i is in range of 32 bits.
   */
  bool operator[](int i) {
    assert((i>=0 && i<32));
    std::uint32_t mask = 1 << i; // mask with a one in bit i and 0 elsewhere
    return (value&mask) == mask; // bitwise And to isolate value of bit i
  }
  
  word_t operator+(const word_t& rhs) {
    word_t new_word(this->value + rhs.value);
    return new_word;
  }

  friend std::ostream& operator<<(std::ostream& os, const word_t& obj) {
    os << static_cast<unsigned int>(obj.value);
    return os;
  }

  word_t& operator=(const word_t& rhs) {
    this->value = rhs.value;
    return *this;
  }  
}; // TODO: Finish Word_t and byte_t documentation


/**
 * @brief byteMicroCircuit is an extension to microCircuit gates with byte_t 
 *   in- and outputs included on top of normal microCircuit functionality.
 * 
 * byteMicroCircuit takes Nbit_in individual bit inputs and Nbyte_in full
 * byte (i.e. 8bit) inputs and maps them via some internal circuitry composed
 * of N_comp sub_components (of any type) to Nbit_out bit outputs and 
 * Nbyte_out byte outputs.
 * 
 * @tparam Nbit_in the number of input bits.
 * @tparam Nbyte_in the number of input bytes.
 * @tparam Nbit_out the number of output bits.
 * @tparam Nbyte_out the number of output bytes.
 * @tparam N_comp the number of sub-components of the byteMicroCircuit.
 */
template <io_t Nbit_in, io_t Nbyte_in, io_t Nbit_out, io_t Nbyte_out, io_t N_comp>
class byteMicroCircuit : public microCircuit<Nbit_in, Nbit_out, N_comp> {
  protected:
    /**
     * @brief byte_input_pointers_ saves the byte inputs.
     */
    std::array<ptr8_t, Nbyte_in> byte_input_pointers_;
    /**
     * @brief byte_output_pointers_ saves the byte outputs.
     */
    std::array<ptr8_t, Nbyte_out> byte_output_pointers_;
  
  public:
    /**
     * @brief 8bit analogue to ground; a byte thats always zero.
     */
    static ptr8_t ground8;
    
    /**
     * @brief print_in prints all bit and byte inputs to std::cout.
     */
    void print_in() {
      for(auto it=this->input_pointers_.begin(); it!=this->input_pointers_.end(); it++) {
        std::cout << *(*it);
      }
      std::cout << 'b';
      for(auto it=byte_input_pointers_.begin(); it!=byte_input_pointers_.end(); it++) {
        std::cout << static_cast<unsigned int>((*it)->value) << ' ';
      }
    }

    /**
     * @brief print_out prints all bit and byte outputs to std::cout.
     */
    void print_out() {
      for(auto it=this->output_pointers_.begin(); it!=this->output_pointers_.end();it++){
        std::cout << *(*it);
      }
      std::cout << 'b';
      for(auto it=byte_output_pointers_.begin(); it!=byte_output_pointers_.end();it++) {
        std::cout << static_cast<unsigned int>((*it)->value) << ' ';
      }
    }

    /**
     * @brief rewire_input is a virtual function that ensures that if 
     *   either bit or byte input pointers change, the internal circuitry
     *   connected to the input is updated.
     */
    virtual void rewire_input() {};
 
    /**
     * @brief connect_byte_input assigns the index-th byte input to connected8.
     * @param connected8 the new byte input location to overwrite with.
     * @param index the index of the byte input to overwrite (indexing only byte inputs).
     * @throws std::domain_error if index out of range
     */
    void connect_byte_input(ptr8_t connected8, io_t index) {
      if (index >= Nbyte_in) {
        throw std::domain_error("Input that was attempted to connect is out of range");
      }
      byte_input_pointers_[index] = connected8;
      rewire_input();
    }

    /**
     * @brief release_byte_output returns the pointer to the index-th byte output.
     * @param index the index of the byte output to be released.
     * @return the pointer to the desired output.
     * @throws std::domain_error if index is out of range
     */
    ptr8_t release_byte_output(io_t index) {
      if (index >= Nbyte_out) {
        throw std::domain_error("Output tried to release is out of range");
      }
      return byte_output_pointers_[index];
    }
};


/**
 * @brief wordMicroCircuit is the extension of byteMicroCircuit that includes word in-
 *   and outputs.
 *
 * wordMicroCircuit extends the bit and byte inputs of byteMicroCircuit with word 
 * (so 32 bit) inputs as well as outputs.
 *
 * @tparam Nbit_in the number of input bits.
 * @tparam Nbyte_in the number of input bytes.
 * @tparam Nword_in the number of input words.
 * @tparam Nbit_out the number of output bits.
 * @tparam Nbyte_out the number of output bytes.
 * @tparam Nword_out the number of output words.
 * @tparam N_comp the number of sub-components.
 */
template <io_t Nbit_in, io_t Nbyte_in, io_t Nword_in, io_t Nbit_out, 
	  io_t Nbyte_out, io_t Nword_out, io_t N_comp>
class wordMicroCircuit : public byteMicroCircuit<Nbit_in, Nbyte_in, 
						Nbit_out, Nbyte_out, N_comp> {
  protected:
    /**
     * @brief word_input_pointers_ saves the word inputs.
     */
    std::array<ptr32_t, Nword_in> word_input_pointers_;
    /**
     * @brief word_output_pointers_ saves the word outputs.
     */
    std::array<ptr32_t, Nword_out> word_output_pointers_;

  public:
    /**
     * @brief ground32 the 32bit analogue to ground; a word thats always zero.
     */
    static ptr32_t ground32;
    
    /**
     * @brief print_in prints bit, byte and word inputs to std::cout.
     */
    void print_in() {
      for (auto it=this->input_pointers_.begin(); 
           it!=this->input_pointers_.end(); it++) {
        std::cout << *(*it);
      }
      std::cout << 'b';
      for (auto it=this->byte_input_pointers_.begin(); 
           it!=this->byte_input_pointers_.end();it++) {
        std::cout << static_cast<unsigned int>((*it)->value) << ' ';
      }
      std::cout << 'w';
      for (auto it=word_input_pointers_.begin();
           it!=word_input_pointers_.end();it++) {
        std::cout << static_cast<unsigned int>((*it)->value) << ' ';
      }
    }

    /**
     * @brief print_out prints bit, byte and word outputs to std::cout.
     */
    void print_out() {
      for (auto it=this->output_pointers_.begin(); 
           it!=this->output_pointers_.end(); it++) {
        std::cout << *(*it);
      }
      std::cout << 'b';
      for (auto it=this->byte_output_pointers_.begin();
           it!=this->byte_output_pointers_.end();it++) {
         std::cout << static_cast<unsigned int>((*it)->value) << ' ';
      }
      std::cout << 'w';
      for (auto it=word_output_pointers_.begin(); 
           it!=word_output_pointers_.end(); it++) {
        std::cout << static_cast<unsigned int>((*it)->value) << ' ';
      }
    }

    /**
     * @brief connect_word_input assigns the index-th word input
     *   to connected32.
     * @param connected32 the new word input location to overwrite with
     * @param index the index of word input to overwrite.
     */
    void connect_word_input(ptr32_t connected32, io_t index) {
      if (index >= Nword_in) {
        throw std::domain_error("Input that was attempted to connect is out of range");
      }
      word_input_pointers_[index] = connected32;
      this->rewire_input();
    }

    /**
     * @brief release_word_output returns index-th word output.
     * @param index the index of the returned word output.
     * @return the pointer to the index-th output.
     * @throws std::domain_error if index is out of range.
     */
    ptr32_t release_word_output(io_t index) {
      if (index >= Nword_out) {
        throw std::domain_error("Output tried to release is out of range");
      }
      return word_output_pointers_[index];
    }
};

/**
 * @brief ground8 initialization, constant "ground" set to zero.
 */
template <io_t Nbit_in, io_t Nbyte_in, io_t Nbit_out, io_t Nbyte_out, io_t N_comp>
ptr8_t byteMicroCircuit<Nbit_in,Nbyte_in,
                        Nbit_out,Nbyte_out,N_comp>::ground8 = 
							std::make_shared<byte_t>(0);

/**
 * @brief ground32 initialization, constant "ground" set to zero.
 */
template <io_t Nbit_in, io_t Nbyte_in, io_t Nword_in,
	  io_t Nbit_out, io_t Nbyte_out, io_t Nword_out, io_t N_comp>
ptr32_t wordMicroCircuit<Nbit_in,Nbyte_in,Nword_in,
  			 Nbit_out,Nbyte_out,Nword_out,N_comp>::ground32 = 
							std::make_shared<word_t>(0);

} //namespace Virtual

#endif
