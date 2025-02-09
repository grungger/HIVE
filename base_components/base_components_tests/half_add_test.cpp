#include "switch_in.hpp"
#include "output.hpp"
#include "half_adder.hpp"

using namespace Virtual;

int main() {

Switch_in inA(false);
Switch_in inB(false);

HalfAdder twobitadd(inA.release_output(0), inB.release_output(0));

std::cout << "0+0 = b";
twobitadd.print_out();
std::cout << std::endl;

inA.change_state(true);
twobitadd.compute_output();
std::cout << "1+0 = b";
twobitadd.print_out();
std::cout << std::endl;

inB.change_state(true);
twobitadd.compute_output();
std::cout << "1+1 = b";
twobitadd.print_out();
std::cout << std::endl;

}
