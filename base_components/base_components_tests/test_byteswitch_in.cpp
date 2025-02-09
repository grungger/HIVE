#include "byteswitch_in.hpp"

using namespace Virtual;

int main() {

byte_t in_nr(25);
ByteSwitch_in input(in_nr);
std::cout << "byte switch with byte_t of 25: ";
input.print_out();
std::cout << std::endl;

ByteSwitch_in input_num(13);
std::cout << "b.s.i with nr of 13: ";
input_num.print_out();
std::cout << std::endl;

input_num.change_state(77);

std::cout << "byteswitch 77: ";
input_num.print_out();
std::cout << std::endl;

}
