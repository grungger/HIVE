/*************************************************
 * @file or3.hpp
 *
 * @brief Implementation of the three bit Or gate.
 *************************************************/
// Includes:
#include "microcircuit.hpp"
#include "or.hpp"
// Header Guards:
#ifndef OR3_H
#define OR3_H

namespace Virtual{

/**
 * @brief Or3 is the three bit implementation of the Or gate using two 2bit Or gates.
 */
class Or3 : public microCircuit<3,1,2> {
  public:
    /**
     * @brief Constructor for Or3 setting inputs and creating two Or gates.
     * @param conA first input.
     * @param conB second input.
     * @param conC third input.
     * @note Although the third input is handled differently, behavior is symmetric.
     */
    Or3(ptr_t conA = ground, ptr_t conB = ground, ptr_t conC = ground);

    /**
     * @brief rewire_input sets the inputs of the first Or gate and the second input 
     *   of the second Or gate to the input_pointers_.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
