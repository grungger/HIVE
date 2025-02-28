/***********************************************
 * @file counter.hpp
 *
 * @brief Implementation of the Counter byteMicroCircuit that tells a program block, 
 *   which instruction to run next, increments every tick and can be overwritten.
 **********************************************/
// Includes: 
#include "bytemicrocircuit.hpp"
#include "byte_mux.hpp"
#include "bytememory.hpp"
#include "byte_adder.hpp"
#include "not.hpp"

// Header Guards:
#ifndef COUNTER_H
#define COUNTER_H

namespace Virtual{

/**
 *
 */
class Counter : public byteMicroCircuit<1,1,0,1,4> {
  public:
    Counter(ptr_t overwrite=ground, ptr32_t value=ground32);
    void rewire_input();
    static const std::string gate_name;
    void compute_output();
    void memory_release();
};

} //namespace Virtual

#endif
