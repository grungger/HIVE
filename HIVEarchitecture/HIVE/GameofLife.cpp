#include <stdexcept>
#include <iostream>
#include "HIVEmind.cpp"

using namespace Virtual;

int main() {
	HIVEmind hive = HIVEmind();
	unsigned int flush = (1u<<24)*7;
	unsigned int immediate1b = (1u<<16);
	unsigned int immediatefull = (1u<<24)*128;
	unsigned int copyR0toDisp = (1u<<24)*3+(1u<<8)*17;
	unsigned int comp = (1u<<24)*2;
	unsigned int copy = (1u<<24)*3;
	unsigned int cond = (1u<<24)*4;
	unsigned int sram = (1u<<24)*64;
	unsigned int dram = (1u<<24)*32;
	unsigned int s1 = (1u<<16);
	unsigned int d1 = (1u<<8);

	// set iter = 0 to Reg14 and itermax N = 10 to Reg15
	std::vector<std::uint32_t> program{
		flush,
		copy+s1*128+s1*10+d1*15, // N in Reg15
		// Initial board
		// for i=0,i<16,i++ ->save i tmp in Reg12
		copy+s1*128+d1*17, // <- loop, line 2
		// copy+dram+s1*128+d1*i
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12,
		immediate1b*2,
		cond+5+s1*12+d1*128+d1*16,
		immediatefull+s1,
		copyR0toDisp,
		immediatefull+d1*128+s1*13,
		copyR0toDisp,
		immediatefull+s1,
		copyR0toDisp,
		// for i=19,i<32,i++ ->save i tmp in Reg12
		copy+s1*128+s1*19+d1*12,
		copy+s1*128+d1*17, // <- loop, line 14
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12,
		immediate1b*14,
		cond+5+s1*12+d1*128+d1*32,
		flush,

	};


	hive.add_lines(program);
	while (true) {
		//std::cout << "tick " << i++ << std::endl;
		try{
		  hive.tick();}
		catch (std::domain_error& e) {
		  break;}
	}
}
