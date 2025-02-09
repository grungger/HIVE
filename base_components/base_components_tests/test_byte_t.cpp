#include "bytemicrocircuit.hpp"
#include <iostream>

using namespace Virtual;

int main() {

byte_t Byte_num(123);

std::cout << "Ctr with 123: " << Byte_num.value << std::endl;

std::cout << "Access 0th bit of 123: " << Byte_num[0] << std::endl;

std::cout << "Output byte_t: " << Byte_num << std::endl;

byte_t Byte_copy(Byte_num);

std::cout << "Ctr with copy of 123: " << Byte_copy.value << std::endl;

Byte_copy = Byte_num + Byte_copy;

std::cout << "Value after addition: " << Byte_copy << std::endl;

byte_t Byte_nr(168);

std::cout << "Display 168 in binary: ";
for (int i=0; i<8; i++) {
  std::cout << Byte_nr[i];
}
std::cout << std::endl;

}
