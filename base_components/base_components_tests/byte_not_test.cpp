#include "byteswitch_in.hpp"
#include "byte_not.hpp"
#include "byte_or.hpp"

using namespace Virtual;

int main() {

ByteSwitch_in input(240);
ByteSwitch_in input2(14);

ByteNot notg(input.release_byte_output(0));
std::cout << "Not(240) = ";
notg.print_out();
std::cout << std::endl;

ByteOr org(input.release_byte_output(0), input2.release_byte_output(0));
std::cout << "Or(240,14) = ";
org.print_out();
std::cout << std::endl;

}
