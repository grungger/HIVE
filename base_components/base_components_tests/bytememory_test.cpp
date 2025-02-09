#include "bytememory.hpp"
#include "byteswitch_in.hpp"
#include "switch_in.hpp"
#include "byteoutput.hpp"

using namespace Virtual;

int main() {

Switch_in load(false);
Switch_in save(false);
ByteSwitch_in value(19);
ByteMemory memory(load.release_output(0), save.release_output(0), value.release_byte_output(0));
ByteOutput out(memory.release_byte_output(0));

std::cout << "no load, no save: ";
memory.compute_output();
out.compute_output();
std::cout << std::endl;

std::cout << "save 19: ";
save.change_state(true);
memory.compute_output();
out.compute_output();
std::cout << std::endl;

std::cout << "load 19: ";
load.change_state(true);
save.change_state(false);
memory.compute_output();
out.compute_output();
std::cout << std::endl;

std::cout << "save 30 and load: ";
save.change_state(true);
value.change_state(30);
memory.compute_output();
out.compute_output();
std::cout << std::endl;

std::cout << "load 30: ";
memory.compute_output();
out.compute_output();
std::cout << std::endl;

}
