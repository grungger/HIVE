#include "byte_adder.hpp"
#include "byteswitch_in.hpp"
#include <iostream>

using namespace Virtual;

int main() {

ByteSwitch_in in1(67);

ByteSwitch_in in2(34);

ByteAdder calc(in1.ground, in1.release_byte_output(0), in2.release_byte_output(0));

std::cout << "67 + 34 = ";

calc.print_out();

std::cout << std::endl;

in1.change_state(22);
in2.change_state(21);
calc.compute_output();

std::cout << "22 + 21 = ";

calc.print_out();

std::cout << std::endl;

in1.change_state(240);
in2.change_state(15);
calc.compute_output();

std::cout << "240 + 15 = ";
calc.print_out();
std::cout << std::endl;

in2.change_state(16);
calc.compute_output();
std::cout << "240 + 16 = ";
calc.print_out();
std::cout << std::endl;

in1.change_state(255);
in2.change_state(255);
calc.compute_output();
std::cout << "255 + 255 = ";
calc.print_out();
std::cout << std::endl;

}
