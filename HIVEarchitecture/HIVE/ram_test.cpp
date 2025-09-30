#include <stdexcept>
#include <iostream>
#include "HIVEmind.cpp"

using namespace Virtual;

int main() {
	HIVEmind hive = HIVEmind(3.0);
	unsigned int flush = (1u<<24)*7;
	unsigned int immediate1b = (1u<<16);
	unsigned int immediatefull = (1u<<24)*128;
	unsigned int copy0toDisp = (1u<<24)*3+(1u<<8)*17;
	unsigned int comp = (1u<<24)*2;
	unsigned int copy = (1u<<24)*3;
	unsigned int cond = (1u<<24)*4;
	unsigned int sram = (1u<<24)*64;
	unsigned int sramIm = (1u<<24)*64+64;
	unsigned int dram = (1u<<24)*32;
	unsigned int dramIm = (1u<<24)*32+32;
	unsigned int s1 = (1u<<16);
	unsigned int d1 = (1u<<8);
	std::vector<std::uint32_t> program{
		flush,
		copy+dramIm+d1*15+s1*128+s1*9, // 9 to RAM15
		immediate1b*7,
		copy+dram+s1*128+s1*1, // 1 to RAM(Reg0=7)
		comp+7, // 14 to Reg3
		copy+sram+d1*4, // RAM(Reg0=7)=1 to Reg4
		copy+s1*3+dram+d1*3, //Reg3=14 to RAM(Reg3=14)
		immediate1b*9,
		copy+d1*10,
		immediate1b*7,
		copy+sram+s1*3+dramIm+d1*255, // RAM(Reg3=14)=14 to RAM255
		copy+sram+dram+d1*10, // RAM(Reg0=7)=1 to RAM(Reg10=9)
		copy+sramIm+s1*14+dramIm+d1*254,
		copy+sramIm+s1*7+dramIm+d1*254
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
