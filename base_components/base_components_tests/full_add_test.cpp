#include "switch_in.hpp"
#include "output.hpp"
#include "full_adder.hpp"

using namespace Virtual;

int main() {

Switch_in inA(false);
Switch_in inB(false);
Switch_in inC(false);

FullAdder threebitadd(inA.release_output(0), inB.release_output(0), inC.release_output(0));

std::cout << "0+0+0 = b";
threebitadd.print_out();
std::cout << std::endl;

inB.change_state(true);
threebitadd.compute_output();
std::cout << "0+1+0 = b";
threebitadd.print_out();
std::cout << std::endl;

inA.change_state(true);
threebitadd.compute_output();
std::cout << "1+1+0 = b";
threebitadd.print_out();
std::cout << std::endl;

inC.change_state(true);
threebitadd.compute_output();
std::cout << "1+1+1 = b";
threebitadd.print_out();
std::cout << std::endl;

}
