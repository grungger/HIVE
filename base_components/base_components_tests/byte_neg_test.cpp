#include "byteswitch_in.hpp"
#include <iostream>
#include "byte_neg.hpp"

using namespace Virtual;

int main() {

ByteSwitch_in input(2);

ByteNeg negator(input.release_byte_output(0));

std::cout << "negator of 2 = ";
negator.print_out();
std::cout << std::endl;

}
