#include <stdexcept>
#include <iostream>
#include "HIVEmind.cpp"

using namespace Virtual;

int main() {
	HIVEmind hive = HIVEmind(10.0);
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

	// Nr of frames:
	unsigned int N = 100;
	
	// nr of init lines
	unsigned int x = 27;

	std::vector<std::uint32_t> program{
		flush,
		// Initial board
		// for i=0,i<8,i++ ->save i tmp in Reg12
		copy+s1*128+d1*17, // 0 to Disp <- loop, line 1
		copy+dram+s1*128+d1*12, // 0 to RAM[i]
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12, // i+=1
		immediate1b, // 1 to Reg0
		cond+5+s1*12+d1*128+d1*8, // if i < 8 go to line 1
		immediatefull+d1, // 2^8 to Reg0
		copyR0toDisp, // 2^8 to Disp
		copy+dram+s1*0+d1*12,
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12, // i+=1
		immediatefull+128+d1*13,
		copyR0toDisp,
		copy+dram+s1*0+d1*12,
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12, // i+=1
		immediatefull+d1,
		copyR0toDisp,
		copy+dram+s1*0+d1*12,
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12, // i+=1
		// for i=11,i<16,i++ ->save i tmp in Reg12
		copy+s1*128+d1*17, // <- loop, line 22 (prev 19)
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12,
		immediate1b*22,
		cond+5+s1*12+d1*128+d1*16,
		flush, // line x=27 (prev 24)
		// Loop 
		//  for each line move current line to other loc -> 35 in RAM,
		//  compute new current line in place from prev line at 34 and
		//  current line at 34 and next line at i+1.
		//  for each line loop once through all 32 bits and treat j=0
		//  and j=31 separately. Since RAM33 is empty(0) i edge cases
		//  are naturally taken care of.
		// Loop frames (until iter=Reg15 >= N)
		copy+s1*128+d1*14, // i=0
		copy+s1*128+dram+32+d1*34, // clear RAM34
		//  Loop lines (until i=Reg14 >= 32)
		copy+sram+dram+32+s1*14+d1*35, // frame[i] at 35, frame [i-1] at 34
		//   Loop bits (until j=Reg13 >= 31 (j=0&31 treated sep)
		//    -> counter saved at Reg10
		copy+s1*128+d1*13, // j=0  ,  LINE 30
		//   bit 0 special treatment
		copy+s1*128+d1*10, // counter=0
		comp+7+s1*14+d1*128+d1,
		copy+s1*3+d1*2, // i+1 at Reg2
		comp+1+sram+64+s1*34+d1*128+d1, // RAM[i-1]&1
		immediate1b*(x+13), // -> SKIP NEXT LINES x+13(39? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&1 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*34+d1*128+d1*2, // RAM[i-1]&2
		immediate1b*(x+18), // ->SKIP NEXT LINES x+18(44? TODO   , LINE 40
		cond+s1*3+d1*128, // if RAM[i-1]&2 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*35+d1*128+d1*2, // RAM[i]&2
		immediate1b*(x+23), // ->SKIP NEXT LINES x+23(49? TODO
		cond+s1*3+d1*128, // if RAM[i]&2 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*128+d1, // RAM[i+1]&1
		immediate1b*(x+28), // ->SKIP NEXT LINES x+28(54? TODO   LINE 50
		cond+s1*3+d1*128, // if RAM[i+1]&1 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*128+d1*2, // RAM[i+1]&2
		immediate1b*(x+33), // ->SKIP NEXT LINES x+33(59? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&2 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		//     Now evaluate cases of counter values
		comp+1+sram+64+s1*35+d1*128+d1*1, // RAM[i]&1
		immediate1b*(x+38), // ->SKIP TO ELIF LINE x+38(64? TODO ,  LINE 60
		cond+s1*3+d1*128, // if RAM[i]&1 = 0
		immediate1b*(x+44), // ->SKIP TO LIVE CELL x+44(70? TODO
		cond+s1*10+d1*128+d1*2, // if counter==2
		immediate1b*(x+44), // ->SKIP TO LIVE CELL x+44(70? TODO
		cond+s1*10+d1*128+d1*3, // elif counter==3
		comp+6+sram+s1*14+d1*128+d1, // BIC RAM_old[i] 1, DEAD CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] 1 set to 0 -> RAM_new[i]
		immediate1b*(x+46), // ->SKIP PAST LIVE CELL x+46(72? TODO
		cond+10, //  else dead cell (skip live)
		comp+3+sram+s1*14+d1*128+d1, // RAM_old[i] | 1, LIVE CELL , LINE 70
		copy+dram+d1*14+s1*3, // RAM_old[i] | 1 -> RAM_new[i]
		comp+7+s1*13+d1*128+d1,
		copy+s1*3+d1*13, // j+=1

		//  Start actual loop at line x+48(74
		copy+s1*128+d1*10, // counter=0, i+1 still at Reg2 from j=0
		comp+9+s1*13+d1*128+d1,
		copy+s1*3+d1,
		comp+15+s1*128+s1+d1, // (1<<j-1)
		copy+s1*3+d1*4, // (1<<j-1) at Reg4
		comp+7+s1*13+d1*128+d1,
		copy+s1*3+d1, //       LINE 80
		comp+15+s1*128+s1+d1*13, // (1<<j)
		copy+s1*3+d1*5, // (1<<j) at Reg5
		comp+15+s1*128+s1+d1, // (1<<j+1)
		copy+s1*3+d1*6, // (1<<j+1) at Reg6
		comp+1+sram+64+s1*34+d1*4, // RAM[i-1]&(1<<j-1)
		immediate1b*(x+64), // -> SKIP NEXT LINES x+64(90? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*34+d1*5, // RAM[i-1]&(1<<j) ,  LINE 90
		immediate1b*(x+69), // ->SKIP NEXT LINES x+69(95? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*34+d1*6, // RAM[i-1]&(1<<j+1)
		immediate1b*(x+74), // ->SKIP NEXT LINES x+74(100? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j+1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*35+d1*4, // RAM[i]&(1<<j-1) ,   LINE 100
		immediate1b*(x+79), // ->SKIP NEXT LINES x+79(105? TODO
		cond+s1*3+d1*128, // if RAM[i]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*35+d1*6, // RAM[i]&(1<<j+1)
		immediate1b*(x+84), // ->SKIP NEXT LINES x+84(110? TODO
		cond+s1*3+d1*128, // if RAM[i]&(1<<j+1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*4, // RAM[i+1]&(1<<j-1)  ,   LINE 110
		immediate1b*(x+89), // ->SKIP NEXT LINES x+89(115? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1 
		comp+1+sram+s1*2+d1*5, // RAM[i+1]&(1<<j)
		immediate1b*(x+94), // ->SKIP NEXT LINES x+94(120? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*6, // RAM[i+1]&(1<<j+1) ,   LINE 120
		immediate1b*(x+99), // ->SKIP NEXT LINES x+99(125? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j+1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		//     Now evaluate cases of counter values
		comp+1+sram+64+s1*35+d1*5, // RAM[i]&(1<<j)
		immediate1b*(x+104), // ->SKIP TO ELIF LINE x+104(130? TODO
		cond+s1*3+d1*128, // if RAM[i]&(1<<j) = 0
		immediate1b*(x+110), // ->SKIP TO LIVE CELL x+110(136? TODO
		cond+s1*10+d1*128+d1*2, // if counter==2
		immediate1b*(x+110), // ->SKIP TO LIVE CELL x+110(136? TODO ,   LINE 130
		cond+s1*10+d1*128+d1*3, // elif counter==3
		comp+6+sram+s1*14+d1*5, // BIC RAM_old[i] (1<<j), DEAD CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] j set to 0 -> RAM_new[i]
		immediate1b*(x+112), // ->SKIP PAST LIVE CELL x+112(138? TODO
		cond+10, //  else dead cell (skip live)
		comp+3+sram+s1*14+d1*5, // RAM_old[i] | (1<<j), LIVE CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] | (1<<j) -> RAM_new[i]
		comp+7+s1*13+d1*128+d1,
		copy+s1*3+d1*13, // j+=1
		immediate1b*(x+48), // finish loop bits x+48
				// (still need to treat j=15) TODO LINE 140
		cond+5+s1*13+d1*128+d1*15,

		// Treat j=15 separately
		copy+s1*128+d1*10, // counter=0
		comp+9+s1*13+d1*128+d1, // +ADDED TALLY NOW +4
		copy+s1*3+d1, // j-1 at Reg1 +ADDED TALLY NOW +5
		comp+15+s1*128+s1+d1, // (1<<j-1)
		copy+s1*3+d1*4, // (1<<j-1) at Reg4
		// comp+7+s1*13+d1*128+d1, -RMVD TALLY NOW +4
		// copy+s1*3+d1, -RMVD TALLY NOW +3
		comp+15+s1*128+s1+d1*13, // (1<<j)
		copy+s1*3+d1*5, // (1<<j) at Reg5
		comp+1+sram+64+s1*34+d1*4, // RAM[i-1]&(1<<j-1)
		immediate1b*(x+128), // -> SKIP NEXT LINES x+128(154? TODO ,   LINE 150
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*34+d1*5, // RAM[i-1]&(1<<j)
		immediate1b*(x+133), // -> SKIP NEXT LINES x+133(159? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1 
		comp+1+sram+64+s1*35+d1*4, // RAM[i]&(1<<j-1)
		immediate1b*(x+138), // ->SKIP NEXT LINES x+138(164? TODO LINE 160
		cond+s1*3+d1*128, // if RAM[i]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*4, // RAM[i+1]&(1<<j-1)
		immediate1b*(x+143), // ->SKIP NEXT LINES x+143(169? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*5, // RAM[i+1]&(1<<j)
		immediate1b*(x+148), // ->SKIP NEXT LINES x+148(174? TODO LINE 170
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		//     Now evaluate cases of counter values
		comp+1+sram+64+s1*35+d1*5, // RAM[i]&(1<<j)
		immediate1b*(x+153), // ->SKIP TO ELIF LINE x+153(179? TODO
		cond+s1*3+d1*128, // if RAM[i]&(1<<j) = 0
		immediate1b*(x+159), // ->SKIP TO LIVE CELL x+159(185? TODO
		cond+s1*10+d1*128+d1*2, // if counter==2
		immediate1b*(x+159), // ->SKIP TO LIVE CELL x+159(185? TODO
		cond+s1*10+d1*128+d1*3, // elif counter==3 ,  LINE 180
		comp+6+sram+s1*14+d1*5, // BIC RAM_old[i] (1<<j), DEAD CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] j set to 0 -> RAM_new[i]
		immediate1b*(x+161), // ->SKIP PAST LIVE CELL x+161(187? TODO
		cond+10, //  else dead cell (skip live)
		comp+3+sram+s1*14+d1*5, // RAM_old[i] | (1<<j), LIVE CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] | (1<<j) -> RAM_new[i]

		//    Now move old i to i-1 aka move RAM 35 to 34
		copy+sram+64+s1*35+dram+32+d1*34,
		comp+7+s1*128+s1+d1*14,
		copy+s1*3+d1*14, // i+=1
		immediate1b*(x+3),// x+3 TODO finish loop lines ,  LINE 190
		cond+5+s1*14+d1*128+d1*16,

		// Now move newly computed RAM to Display
		copy+s1*128+d1*7, // y=0 at Reg7
		copy+sram+s1*7+d1*17, // RAM to Disp,
		comp+7+s1*7+d1*128+d1,
		copy+s1*3+d1*7, // y+=1
		immediate1b*(x+167), // x+167 LOOP TODO
		cond+5+s1*7+d1*128+d1*16,
		flush,
		comp+7+s1*128+s1+d1*15,
		copy+s1*3+d1*15, // iter+=1
		immediate1b*(x+1),// x+1 TODO finish loop frames
		cond+5+s1*15+d1*128+d1*N, 

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
