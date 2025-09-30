/*****************************************
 * @file SourceDestDecoder.hpp
 * 
 * @brief Implementation of SourceDestDecoderHIVE which decodes 
 *   the opcode of the HIVE architecture.
 *****************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include "word_splitter.hpp"
#include "threebitdecoder.hpp"
#include "fivebitdecoder.hpp"

// Header Guards:
#ifndef SOURCEDESTDECODERHIVE_H
#define SOURCEDESTDECODERHIVE_H

namespace Virtual{

/**
 * @brief SourceDestDecoderHIVE decodes a 32bit instruction set.
 *
 * ByteA (2^0-2^7) is operators
 * ByteB (2^8-2^15) is destionations
 * ByteC (2^16-2^23) is sources
 * ByteD (2^24-2^31) is mode
 * Available modes are:
 *   0 = immediate (byte) -> ByteC to Reg0
 *   1 = immediate (halfword) -> ByteB + 2^8*ByteC to Reg0
 *   2 = compute -> Reg(ByteC) *(ByteA) Reg(ByteB) to Reg3
 *   3 = copy -> Reg(ByteC) to Reg(ByteB)
 *   4 = condition -> if (Reg(ByteC) <>(ByteA) Reg(ByteB)): R0 to Counter
 *   7 = flush display
 *   Flag bits:
 *   32 = ByteB is RAM address
 *   64 = ByteC is RAM address
 *   128 = immediate (word) -> full opcode minus highest bit to Reg0
 *
 * The possible addresses are:
 *   0-15: Reg0 - Reg15
 *   16: RC (flag storage->ByteRegister)
 *   17: Display (destination only)
 *   >128: Immediate value (ignoring bit 128)
 *   any: RAM address if RAM mode
 *
 * The SourceDestDecoderHIVE outputs are split up as follows:
 *   First decoding the mode:
 *     output_pointers 0 to 5 for modes and 6, 7, 8 for mode flags
 *   Secondly decoding sources:
 *     output_pointers 9 to 24 for Reg, 25 for RC and 26 as Imm flag
 *   Third decoding destinations:
 *     output_pointers 27 to 42 for Reg,
 *     		43 for RC, 44 for Display and 45 as Imm flag
 *   Fourth outputting flags for RAM.
 *     output_pointers 46, 47 are RAM flag for B and C.
 * Note: operators are not decoded here.
 */
class SourceDestDecoderHIVE : public wordMicroCircuit<0,0,1,48,0,0,8> {
  public:
    /**
     * @brief Constructor sets up the decoder.
     */
    SourceDestDecoderHIVE(ptr32_t input=ground32);

    /**
     * @brief rewire_input resets internal circuitry in case inputs changed.
     */
    void rewire_input();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
