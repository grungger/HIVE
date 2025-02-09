#include "byte_maker.hpp"
#include "byte_splitter.hpp"
#include "byteswitch_in.hpp"

using namespace Virtual;

int main() {

byte_t inp_byte(37);

ByteSwitch_in input(inp_byte);
input.print_out();
std::cout << std::endl;
ByteSplitter split(input.release_byte_output(0));

ByteMaker collapse( ByteMaker::ground,
		split.release_output(0),
		split.release_output(1),
		split.release_output(2),
		split.release_output(3),
		split.release_output(4),
		split.release_output(5),
		split.release_output(6) ) ;

collapse.print_out();
std::cout << std::endl;
}
