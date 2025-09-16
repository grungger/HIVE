/*****************************************
 * @file RAM_test.cpp
 *****************************************/
// Includes:
#include "RAM.hpp"
#include "word_wire.hpp"
#include "switch_in.hpp"
#include "word_switch_in.hpp"
#include <sstream>
#include <iostream>
#include <cmath>
#include <string>
#include <initializer_list>
#include <utility>

using namespace Virtual;

std::string line(std::initializer_list< std::pair<int,std::string> > replac={}) {
  std::string output;
  for (int B=0; B<16; B++) {
    std::vector<std::string> vec(16, "0");
    for (auto pair : replac ) {
      int idx = pair.first;
      std::string val = pair.second;
      if (idx/16 == B) {
        vec[idx-B*16] = val;
      }
    }
    std::string line;
    for (auto it=vec.begin(); it<vec.end(); it++) {
      line += *it;
      line += " ";
    }
    line += "\n";
    output += line;
  }
  return output;
}



int main() {
// Testing following operations: copy input to B, compute A, compute B, compute A B, copy from A, copy from A to B
//   each operation occurs with a computation cycle with: 1) memory_release, 1b) if wire (for copy A to B) compute, 2) compute_output
//   all operations should occur within one tick and be correct.
std::stringstream buffer;
std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
Switch_in computeCopy(true);
Switch_in Aload(false);
Switch_in Btog(true);
ByteSwitch_in Aad(0);
ByteSwitch_in Bad(11);
// WordSwitch_in full_opcode(std::pow(2,24)+std::pow(2,25)+std::pow(2,29)+std::pow(2,8)*128); // opcode: 3+32=35 (copy to B)
// WordSwitch_in full_opcode(std::pow(2,30)+std::pow(2,25)+std::pow(2,16)*132+std::pow(2,8)*27+13); // compute A@132,B@27
WordSwitch_in value(4294967295);
RAM RAM_comp(   computeCopy.release_output(0),
		Aload.release_output(0),
		Btog.release_output(0),
		Aad.release_byte_output(0),
		Bad.release_byte_output(0),
		value.release_word_output(0) );

// Testing Copy to B
RAM_comp.printRAM(); // expected: line()
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.printRAM(); // expected: line({{11,"4294967295"}})
Bad.change_state(118);
value.change_state(3);
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.printRAM(); // expected: line({{11,"4294967295"},{118,"3"}})
Bad.change_state(11);
value.change_state(77); 
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.printRAM(); // expected: line({{11,"77"},{118,"3"}})
Bad.change_state(5);
value.change_state(99);
RAM_comp.memory_release();
RAM_comp.compute_output();
Bad.change_state(245);
RAM_comp.memory_release();
RAM_comp.compute_output();
Bad.change_state(189);
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.printRAM(); // expected: line({{5,"99"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}})

// Testing Compute A
computeCopy.change_state(false);
Aload.change_state(true);
Btog.change_state(false);
Aad.change_state(13);
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.printRAM(); // expected: line({{5,"99"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}})
RAM_comp.print_out(); // expected: bw0 0
Aad.change_state(11);
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.printRAM(); // expected: line({{5,"99"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}})
RAM_comp.print_out(); // expected: bw77 0

// Testing Compute B
Aload.change_state(false);
Btog.change_state(true);
Aad.change_state(118);
Bad.change_state(11);
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.print_out(); // expected: bw77 77 
Bad.change_state(245);
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.print_out(); // expected: bw77 99 

// Testing Compute A and B
Aload.change_state(true);
Bad.change_state(255);
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.print_out(); // expected: bw3 0  

// Testing copy from A
Btog.change_state(false);
computeCopy.change_state(true);
Aad.change_state(5);
Bad.change_state(11);
RAM_comp.memory_release();
RAM_comp.compute_output();
RAM_comp.print_out(); // expected: bw99 0  

// Testing copy from A to B
WordWire wire( RAM_comp.release_word_output(0) );
RAM_comp.connect_word_input(wire.release_word_output(0),0);
// full_opcode.change_state(std::pow(2,24)+std::pow(2,25)+std::pow(2,30)+std::pow(2,29)+std::pow(2,16)*128+std::pow(2,8)*3);
computeCopy.change_state(true);
Aload.change_state(true);
Btog.change_state(true);
Aad.change_state(118);
Bad.change_state(1);
RAM_comp.memory_release();
wire.compute_output();
RAM_comp.compute_output();
RAM_comp.print_out(); // expected: bw3 0 
RAM_comp.printRAM(); // expected: line({{1,"3"},{5,"99"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}})
Aad.change_state(1);
Bad.change_state(5);
RAM_comp.memory_release();
wire.compute_output();
RAM_comp.compute_output();
RAM_comp.print_out(); // expected: bw3 0  
RAM_comp.printRAM(); // expected: line({{1,"3"},{5,"3"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}})
Aad.change_state(1);
Bad.change_state(1);
RAM_comp.memory_release();
wire.compute_output();
RAM_comp.compute_output();
RAM_comp.print_out(); // expected: bw3 0  
RAM_comp.printRAM(); // expected: line({{1,"3"},{5,"3"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}})

std::cout.rdbuf(old);

// Prediction:
std::string expectedOutput;
expectedOutput += line() + line({{11,"4294967295"}}) + line({{11,"4294967295"},{118,"3"}}) 
			+ line({{11,"77"},{118,"3"}}) + line({{5,"99"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}})  // Copy to B
		       	+ line({{5,"99"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}}) + "bw0 0 " 
			+ line({{5,"99"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}}) + "bw77 0 "  // Compute A
			+ "bw77 77 " + "bw77 99 " // Compute B
			+ "bw3 0 " // Compute A and B
			+ "bw99 0 " // Copy from A 
			+ "bw3 0 " + line({{1,"3"},{5,"99"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}})
			+ "bw3 0 " + line({{1,"3"},{5,"3"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}})
			+ "bw3 0 " + line({{1,"3"},{5,"3"},{11,"77"},{118,"3"},{189,"99"},{245,"99"}}); 


std::string capturedOutput = buffer.str();


if (capturedOutput != expectedOutput) {
  std::cerr << "Expected: " << expectedOutput << std::endl;
  std::cerr << "Output: " << capturedOutput << std::endl;
  throw std::logic_error("Test failed!");
}

}		
