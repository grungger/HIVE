#include <stdexcept>
#include <iostream>
#include "HIVEmind.cpp"

using namespace Virtual;

int main() {
	HIVEmind hive = HIVEmind();
	unsigned int flush = (1u<<24)*7;
	unsigned int immediate1b = (1u<<16);
	unsigned int immediatefull = (1u<<24)*128;
	unsigned int copy0toDisp = (1u<<24)*3+(1u<<8)*17;
	unsigned int comp = (1u<<24)*2;
	unsigned int copy = (1u<<24)*3;
	unsigned int cond = (1u<<24)*4;
	unsigned int sram = (1u<<24)*64;
	unsigned int dram = (1u<<24)*32;
	unsigned int s1 = (1u<<16);
	unsigned int d1 = (1u<<8);
	std::vector<std::uint32_t> program{
		flush,
		immediate1b,
		copy0toDisp,
		immediate1b*2,
		copy0toDisp,
		immediate1b*4,
		copy0toDisp,
		immediate1b*8,
		copy0toDisp,
		immediate1b*16,
		copy0toDisp,
		immediate1b*32,
		copy0toDisp,
		immediate1b*64,
		copy0toDisp,
		flush
       		};
	std::vector<std::uint32_t> program2{
		flush,
		immediatefull+s1,
		copy+d1,
		immediatefull+128*d1,
		copy+d1*2,
		comp+s1+d1*2+7,
		copy+s1+d1*17,
		copy+s1*2+d1*17,
		copy+s1*3+d1*17,
		copy+s1+d1*17,
		copy+s1*2+d1*17,
		copy+s1*3+d1*17,
		flush,
		copy+s1*2+d1*17,
		copy+s1*3+d1*17,
		copy+s1*1+d1*17,
		copy+s1*2+d1*17,
		copy+s1*3+d1*17,
		copy+s1*1+d1*17,
		flush,
		copy+s1*3+d1*17,
		copy+s1*1+d1*17,
		copy+s1*2+d1*17,
		copy+s1*3+d1*17,
		copy+s1*1+d1*17,
		copy+s1*2+d1*17,
		flush,
		copy+s1+d1*17,
		copy+s1*2+d1*17,
		copy+s1*3+d1*17,
		copy+s1+d1*17,
		copy+s1*2+d1*17,
		copy+s1*3+d1*17,
		flush
		};
	std::vector<std::uint32_t> program3{
		flush,
		copy+s1*128+s1*9+d1*6, // 9 to Reg6
		copy+s1*128+s1+d1*2, // 1 to Reg2
		copy+s1*2+d1*17, // Reg2 to Disp
		comp+7+s1*2+d1*2, // Reg2+Reg2 to Reg3 <--loop start
		copy+s1*3+d1*2, // Reg3 to Reg2 (=R2*=2)
		copy+s1*2+d1*17, // display Reg2
		comp+7+s1*128+s1+d1*5, // 1+Reg5 to Reg3
		copy+s1*3+d1*5, // Reg3 to Reg5 (=R5++)
		immediate1b*4,
		cond+5+s1*5+d1*6, // if R5<9 go to 4 aka loop start
		//cond+11,
		flush // else flush
	};
	std::vector<std::uint32_t> program4{
		flush,
		copy+dram+s1*128+s1*33+d1*4, // 33 to RAM4
		copy+dram+s1*128+s1*17+d1*5, // 17 to RAM5
		copy+s1*4+d1*17, // test whether still 0
		copy+s1*5+d1*17, // test whether still 0
		copy+sram+s1*4+d1*17,
		copy+sram+s1*5+d1*17,
		copy+dram+sram+s1*4+d1*1,
		copy+sram+s1*1+d1*17,
		flush
	};


	hive.add_lines(program4);
	while (true) {
		//std::cout << "tick " << i++ << std::endl;
		try{
		  hive.tick();}
		catch (std::domain_error& e) {
		  break;}
	}
}
