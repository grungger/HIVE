#include "byteswitch_in.hpp"
#include <iostream>
#include "byte_splitter.hpp"

using namespace Virtual;

int main() {

ByteSwitch_in input(39);
std::cout << "splitting ";
input.print_out();
std::cout << std::endl;

ByteSplitter split(input.release_byte_output(0));
split.print_out();

input.change_state(0);

split.compute_output();
std::cout << "splitting 0 into bits: ";
split.print_out();
std::cout << std::endl;

input.change_state(13);
split.compute_output();
std::cout << "splitting 13 ";
split.print_out();
std::cout << std::endl;

}
