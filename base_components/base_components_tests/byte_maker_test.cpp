#include "byte_maker.hpp"
#include "byte_splitter.hpp"
#include "byteswitch_in.hpp"
#include <iostream>

using namespace Virtual;

int main() {

ByteSwitch_in input(17);

ByteSplitter split(input.release_byte_output(0));

ByteArg arger;
arger.in1 = split.release_output(0);
arger.in2 = split.release_output(1);
arger.in3 = split.release_output(2);
arger.in4 = split.release_output(3);
arger.in5 = split.release_output(4);
arger.in6 = split.release_output(5);
arger.in7 = split.release_output(6);
arger.in8 = split.release_output(7);

ByteMaker maker(arger);
std::cout << "Input 17 should output 17: ";
maker.print_out();
std::cout << std::endl;
}
