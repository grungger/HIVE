#include "switch_in.hpp"
#include "output.hpp"

using namespace Virtual;

int main() {

Switch_in input(true);

ptr_t connector = input.release_output(0);

Output output(connector);

input.print_in();
input.print_out();
output.print_in();
output.print_out();
std::cout << std::endl;

output.compute_output();

input.change_state(false);

output.compute_output();

Output empty;

empty.compute_output();

}
