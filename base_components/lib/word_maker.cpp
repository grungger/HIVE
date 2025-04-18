#include "word_maker.hpp"

namespace Virtual{

ByteMaker::ByteMaker(ptr_t in1, ptr_t in2, ptr_t in4, ptr_t in8, 
                     ptr_t in16, ptr_t in32, ptr_t in64, ptr_t in128) {
  input_pointers_[0] = in1;
  input_pointers_[1] = in2;
  input_pointers_[2] = in4;
  input_pointers_[3] = in8;
  input_pointers_[4] = in16;
  input_pointers_[5] = in32;
  input_pointers_[6] = in64;
  input_pointers_[7] = in128;
  std::uint8_t byte_value = 0;
  for (int i=0; i<8; i++) {
    byte_value |= ((*(input_pointers_[i])) << i);
  }
  byte_output_pointers_[0] = std::make_shared<byte_t>(byte_value);
}

ByteMaker::ByteMaker(ByteArg args) {
  for (int i=0; i<8; i++) {
    input_pointers_[i] = args.bits[i];
  }
  std::uint8_t byte_value = 0;
  for (int i=0; i<8; i++) {
    byte_value |= ((*(input_pointers_[i])) << i);
  }
  byte_output_pointers_[0] = std::make_shared<byte_t>(byte_value);
}

void ByteMaker::compute_output() {
  std::uint8_t byte_value = 0;
  for (int i=0; i<8; i++) {
    byte_value |= ((*(input_pointers_[i])) << i);
  }
  byte_t temp(byte_value);
  *(byte_output_pointers_[0]) = temp;
}

const std::string ByteMaker::gate_name = "ByteMaker";


// WordMaker implementations:
WordMaker::WordMaker(ptr_t in1, ptr_t in2, ptr_t in3, ptr_t in4,
              ptr_t in5, ptr_t in6, ptr_t in7, ptr_t in8,
              ptr_t in9, ptr_t in10, ptr_t in11, ptr_t in12,
              ptr_t in13, ptr_t in14, ptr_t in15, ptr_t in16,
              ptr_t in17, ptr_t in18, ptr_t in19, ptr_t in20,
              ptr_t in21, ptr_t in22, ptr_t in23, ptr_t in24,
              ptr_t in25, ptr_t in26, ptr_t in27, ptr_t in28,
              ptr_t in29, ptr_t in30, ptr_t in31, ptr_t in32) {
  input_pointers_[0] = in1;
  input_pointers_[1] = in2;
  input_pointers_[2] = in3;
  input_pointers_[3] = in4;
  input_pointers_[4] = in5;
  input_pointers_[5] = in6;
  input_pointers_[6] = in7;
  input_pointers_[7] = in8;
  input_pointers_[8] = in9;
  input_pointers_[9] = in10;
  input_pointers_[10] = in11;
  input_pointers_[11] = in12;
  input_pointers_[12] = in13;
  input_pointers_[13] = in14;
  input_pointers_[14] = in15;
  input_pointers_[15] = in16;
  input_pointers_[16] = in17;
  input_pointers_[17] = in18;
  input_pointers_[18] = in19;
  input_pointers_[19] = in20;
  input_pointers_[20] = in21;
  input_pointers_[21] = in22;
  input_pointers_[22] = in23;
  input_pointers_[23] = in24;
  input_pointers_[24] = in25;
  input_pointers_[25] = in26;
  input_pointers_[26] = in27;
  input_pointers_[27] = in28;
  input_pointers_[28] = in29;
  input_pointers_[29] = in30;
  input_pointers_[30] = in31;
  input_pointers_[31] = in32;

  std::uint32_t word_value = 0;
  for (int i=0; i<32; i++) {
    word_value |= ((*(input_pointers_[i])) << i);
  }
  word_output_pointers_[0] = std::make_shared<word_t>(word_value);
}

WordMaker::WordMaker(ByteArg arg1, ByteArg arg2, ByteArg arg3, ByteArg arg4) {
  // arg1
  int index = 0;
  for (int j=0; j<8; j++) {
    index = j;
    input_pointers_[index] = arg1.bits[j];
  }
  // arg2
  for (int j=0; j<8; j++) {
    index = j+8;
    input_pointers_[index] = arg2.bits[j];
  }
  // arg3
  for (int j=0; j<8; j++) {
    index = j+16;
    input_pointers_[index] = arg3.bits[j];
  }
  // arg4
  for (int j=0; j<8; j++) {
    index = j+24;
    input_pointers_[index] = arg4.bits[j];
  }
  std::uint32_t word_value = 0;
  for (int i=0; i<32; i++) {
    word_value |= ((*(input_pointers_[i])) << i);
  }
  word_output_pointers_[0] = std::make_shared<word_t>(word_value);
}

WordMaker::WordMaker(WordArg arg) {
  std::uint32_t word_value = 0;
  for (int i=0; i<32; i++) {
    input_pointers_[i] = arg.bits[i];
    word_value |= ((*(input_pointers_[i])) << i);
  }
  word_output_pointers_[0] = std::make_shared<word_t>(word_value);
}

void WordMaker::compute_output() {
  std::uint32_t word_value = 0;
  for (int i=0; i<32; i++) {
    word_value |= ((*(input_pointers_[i])) << i);
  }
  word_t temp(word_value);
  *(word_output_pointers_[0]) = temp;
}

const std::string WordMaker::gate_name = "WordMaker";

} //namespace Virtual
