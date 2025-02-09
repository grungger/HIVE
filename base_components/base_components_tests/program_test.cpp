#include "program.hpp"
#include "counter.hpp"
#include "byteoutput.hpp"
#include "switch_in.hpp"
#include "byteswitch_in.hpp"
#include <vector>
#include <iostream>

using namespace Virtual;

int main() {

Program program;

ByteOutput out1(program.release_byte_output(0));
ByteOutput out2(program.release_byte_output(1));
ByteOutput out3(program.release_byte_output(2));
ByteOutput out4(program.release_byte_output(3));

Switch_in jump(false);

Counter counter(jump.release_output(0), program.release_byte_output(0));
ByteOutput countout(counter.release_byte_output(0));

program.connect_byte_input(counter.release_byte_output(0),0);

std::vector<byte_t> lines{1,2,3,4,1,20,30,40,0,21,22,23,30,31,32,33,100,101,102,103};
program.add_lines(lines);

counter.compute_output();
program.compute_output();
out1.compute_output();
out2.compute_output();
out3.compute_output();
out4.compute_output();
counter.compute_output();
countout.compute_output();
program.compute_output();
out1.compute_output();
out2.compute_output();
out3.compute_output();
out4.compute_output();
jump.change_state(true);
counter.compute_output();
countout.compute_output();
program.compute_output();
out1.compute_output();
out2.compute_output();
out3.compute_output();
out4.compute_output();
jump.change_state(false);
counter.compute_output();
program.compute_output();
out1.compute_output();
out2.compute_output();
out3.compute_output();
out4.compute_output();
std::cout << std::endl;

Program program2;
Switch_in overwrite2;
ByteSwitch_in val2;
Counter counter2(overwrite2.release_output(0),val2.release_byte_output(0));
program2.connect_byte_input(counter2.release_byte_output(0),0);

std::vector<byte_t> lines2{1,2,3,4,5,6,7,8,9,10,11,12};
program2.add_lines(lines2);

counter2.compute_output();
program2.compute_output();
program2.print_out();
overwrite2.change_state(true);
counter2.compute_output();
program2.compute_output();
program2.print_out();
counter2.compute_output();
program2.compute_output();
program2.print_out();

}
