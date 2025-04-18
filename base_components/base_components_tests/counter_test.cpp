#include "counter.hpp"
#include "switch_in.hpp"
#include "word_switch_in.hpp"

using namespace Virtual;

int main() {

Switch_in overwrite(false);
ByteSwitch_in new_val(0);
ByteCounter counter(overwrite.release_output(0), new_val.release_byte_output(0));
std::cout << "After initialization: ";
counter.print_in();
counter.print_out();
std::cout << std::endl;

counter.compute_output();
std::cout << "One computation: ";
counter.print_in();
counter.print_out();
std::cout << std::endl;

counter.compute_output();
std::cout << "Two computations: ";
counter.print_in();
counter.print_out();
std::cout << std::endl;

counter.compute_output();
std::cout << "Three computations: ";
counter.print_out();
std::cout << std::endl;

overwrite.change_state(true);
new_val.change_state(17);
counter.compute_output();
std::cout << "Overwrite with 17: ";
counter.print_in();
counter.print_out();
std::cout << std::endl;

counter.compute_output();
std::cout << "Another compute: ";
counter.print_out();
std::cout << std::endl;

overwrite.change_state(false);
counter.compute_output();
std::cout << "Should be incrementing: ";
counter.print_out();
std::cout << std::endl;

counter.compute_output();
std::cout <<"incrementing now? ";
counter.print_out();
std::cout << std::endl;
}
