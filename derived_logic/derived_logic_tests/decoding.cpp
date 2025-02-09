#include "onebitdecoder.hpp"
#include "switch_in.hpp"
#include "threebitdecoder.hpp"

using namespace Virtual;

int main() {

Switch_in input(false);
OneBitDecoder onedecoder(input.release_output(0));

std::cout << "Decoded 0: ";
onedecoder.print_out();
std::cout << std::endl;

std::cout << "Decoded 1: ";
input.change_state(true);
onedecoder.compute_output();
onedecoder.print_out();
std::cout << std::endl;

std::cout << "Now 3bitdecoding: " << std::endl;
Switch_in input1(false);
Switch_in input2(false);
Switch_in input4(false);

ThreeBitDecoder threedecoder(input1.release_output(0), input2.release_output(0), input4.release_output(0));

std::cout << "Decoded 0: ";
threedecoder.compute_output();
threedecoder.print_out();
std::cout << std::endl;

std::cout << "Decoded 1: ";
input1.change_state(true);
threedecoder.compute_output();
threedecoder.print_out();
std::cout << std::endl;

std::cout << "Decoded 2: ";
input1.change_state(false);
input2.change_state(true);
threedecoder.compute_output();
threedecoder.print_out();
std::cout << std::endl;

std::cout << "Decoded 7: ";
input1.change_state(true);
input4.change_state(true);
threedecoder.compute_output();
threedecoder.print_out();
std::cout << std::endl;

}
