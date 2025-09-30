#include <stdexcept>
#include <iostream>
#include "HIVEmind.cpp"

using namespace Virtual;

int main() {
	HIVEmind hive = HIVEmind(3.0);
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

	std::vector<std::uint32_t> program{
		flush,
		// Initial board
		// for i=0,i<1,i++ ->save i tmp in Reg12
		copy+s1*128+d1*17, // 0 to Disp <- loop, line 1
		copy+dram+s1*128+d1*12, // 0 to RAM[i]
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12, // i+=1
		immediate1b, // 1 to Reg0
		cond+5+s1*12+d1*128+d1*1, // if i < 1 go to line 1
		immediatefull+7, // 7 to Reg0
		copyR0toDisp, // 7 to Disp
		copy+dram+s1*0+d1*12,
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12, // i+=1
		cond+11,
		cond+11,
		cond+11,
		cond+11,
		cond+11,
		cond+11,
		cond+11,
		cond+11,
		cond+11,
		// rmvd cond+11,
		// for i=2,i<3,i++ ->save i tmp in Reg12
		copy+s1*128+d1*17, // <- loop, line 21(22 (prev 19)
		comp+7+s1*128+s1+d1*12,
		copy+s1*3+d1*12,
		immediate1b*21,
		cond+5+s1*12+d1*128+d1*3,
		flush, // line 26(27 (prev 24)
		// Loop 
		//  for each line move current line to other loc -> 35 in RAM,
		//  compute new current line in place from prev line at 34 and
		//  current line at 34 and next line at i+1.
		//  for each line loop once through all 32 bits and treat j=0
		//  and j=31 separately. Since RAM33 is empty(0) i edge cases
		//  are naturally taken care of.
		// Loop frames (until iter=Reg15 >= N)
		copy+s1*128+d1*14, // i=0
		//  Loop lines (until i=Reg14 >= 3)
		//  TODO TODO TODO TODO  we need to clear remove RAM34
		copy+s1*128+dram+32+d1*34, 
		copy+sram+dram+32+s1*14+d1*35, // TODO FIX TODO FIX TODO frame[i] at 35, frame [i-1] at 34
		//   Loop bits (until j=Reg13 >= 3 (j=0&31 treated sep)
		//    -> counter saved at Reg10
		copy+s1*128+d1*13, // j=0  ,  LINE 30
		//   bit 0 special treatment
		copy+s1*128+d1*10, // counter=0
		comp+7+s1*14+d1*128+d1,
		copy+s1*3+d1*2, // i+1 at Reg2
		comp+1+sram+64+s1*34+d1*128+d1, // RAM[i-1]&1
		immediate1b*39, // -> SKIP NEXT LINES 39? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&1 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*34+d1*128+d1*2, // RAM[i-1]&2
		immediate1b*44, // ->SKIP NEXT LINES 44? TODO   , LINE 40
		cond+s1*3+d1*128, // if RAM[i-1]&2 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*35+d1*128+d1*2, // RAM[i]&2
		immediate1b*49, // ->SKIP NEXT LINES 49? TODO
		cond+s1*3+d1*128, // if RAM[i]&2 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*128+d1, // RAM[i+1]&1
		immediate1b*54, // ->SKIP NEXT LINES 54? TODO   LINE 50
		cond+s1*3+d1*128, // if RAM[i+1]&1 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*128+d1*2, // RAM[i+1]&2
		immediate1b*59, // ->SKIP NEXT LINES 59? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&2 = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		//     Now evaluate cases of counter values
		comp+1+sram+64+s1*35+d1*128+d1*1, // RAM[i]&1
		immediate1b*64, // ->SKIP TO ELIF LINE 64? TODO ,  LINE 60
		cond+s1*3+d1*128, // if RAM[i]&1 = 0
		immediate1b*70, // ->SKIP TO LIVE CELL 70? TODO
		cond+s1*10+d1*128+d1*2, // if counter==2
		immediate1b*70, // ->SKIP TO LIVE CELL 70? TODO
		cond+s1*10+d1*128+d1*3, // elif counter==3
		comp+6+sram+s1*14+d1*128+d1, // BIC RAM_old[i] 1, DEAD CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] 1 set to 0 -> RAM_new[i]
		immediate1b*72, // ->SKIP PAST LIVE CELL 72? TODO
		cond+10, //  else dead cell (skip live)
		comp+3+sram+s1*14+d1*128+d1, // RAM_old[i] | 1, LIVE CELL , LINE 70
		copy+dram+d1*14+s1*3, // RAM_old[i] | 1 -> RAM_new[i]
		comp+7+s1*13+d1*128+d1,
		copy+s1*3+d1*13, // j+=1

		//  Start actual loop at line 74
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
		immediate1b*90, // -> SKIP NEXT LINES 90? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*34+d1*5, // RAM[i-1]&(1<<j) ,  LINE 90
		immediate1b*95, // ->SKIP NEXT LINES 95? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*34+d1*6, // RAM[i-1]&(1<<j+1)
		immediate1b*100, // ->SKIP NEXT LINES 100? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j+1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*35+d1*4, // RAM[i]&(1<<j-1) ,   LINE 100
		immediate1b*105, // ->SKIP NEXT LINES 105? TODO
		cond+s1*3+d1*128, // if RAM[i]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*35+d1*6, // RAM[i]&(1<<j+1)
		immediate1b*110, // ->SKIP NEXT LINES 110? TODO
		cond+s1*3+d1*128, // if RAM[i]&(1<<j+1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*4, // RAM[i+1]&(1<<j-1)  ,   LINE 110
		immediate1b*115, // ->SKIP NEXT LINES 115? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1 
		comp+1+sram+s1*2+d1*5, // RAM[i+1]&(1<<j)
		immediate1b*120, // ->SKIP NEXT LINES 120? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*6, // RAM[i+1]&(1<<j+1) ,   LINE 120
		immediate1b*125, // ->SKIP NEXT LINES 125? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j+1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		//     Now evaluate cases of counter values
		comp+1+sram+64+s1*35+d1*5, // RAM[i]&(1<<j)
		immediate1b*130, // ->SKIP TO ELIF LINE 130? TODO
		cond+s1*3+d1*128, // if RAM[i]&(1<<j) = 0
		immediate1b*136, // ->SKIP TO LIVE CELL 136? TODO
		cond+s1*10+d1*128+d1*2, // if counter==2
		immediate1b*136, // ->SKIP TO LIVE CELL 136? TODO ,   LINE 130
		cond+s1*10+d1*128+d1*3, // elif counter==3
		comp+6+sram+s1*14+d1*5, // BIC RAM_old[i] (1<<j), DEAD CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] j set to 0 -> RAM_new[i]
		immediate1b*138, // ->SKIP PAST LIVE CELL 138? TODO
		cond+10, //  else dead cell (skip live)
		comp+3+sram+s1*14+d1*5, // RAM_old[i] | (1<<j), LIVE CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] | (1<<j) -> RAM_new[i]
		comp+7+s1*13+d1*128+d1,
		copy+s1*3+d1*13, // j+=1
		immediate1b*74, // finish loop bits 
				// (still need to treat j=2) TODO LINE 140
		cond+5+s1*13+d1*128+d1*2,

		// Treat j=2 separately
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
		immediate1b*154, // -> SKIP NEXT LINES 154? TODO ,   LINE 150
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+64+s1*34+d1*5, // RAM[i-1]&(1<<j)
		immediate1b*159, // -> SKIP NEXT LINES 159? TODO
		cond+s1*3+d1*128, // if RAM[i-1]&(1<<j) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1 
		comp+1+sram+64+s1*35+d1*4, // RAM[i]&(1<<j-1)
		immediate1b*164, // ->SKIP NEXT LINES 164? TODO LINE 160
		cond+s1*3+d1*128, // if RAM[i]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*4, // RAM[i+1]&(1<<j-1)
		immediate1b*169, // ->SKIP NEXT LINES 169? TODO
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j-1) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		comp+1+sram+s1*2+d1*5, // RAM[i+1]&(1<<j)
		immediate1b*174, // ->SKIP NEXT LINES 174? TODO LINE 170
		cond+s1*3+d1*128, // if RAM[i+1]&(1<<j) = 0
		comp+7+s1*10+d1*128+d1,
		copy+s1*3+d1*10, // counter+=1
		//     Now evaluate cases of counter values
		comp+1+sram+64+s1*35+d1*5, // RAM[i]&(1<<j)
		immediate1b*179, // ->SKIP TO ELIF LINE 179? TODO
		cond+s1*3+d1*128, // if RAM[i]&(1<<j) = 0
		immediate1b*185, // ->SKIP TO LIVE CELL 185? TODO
		cond+s1*10+d1*128+d1*2, // if counter==2
		immediate1b*185, // ->SKIP TO LIVE CELL 185? TODO
		cond+s1*10+d1*128+d1*3, // elif counter==3 ,  LINE 180
		comp+6+sram+s1*14+d1*5, // BIC RAM_old[i] (1<<j), DEAD CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] j set to 0 -> RAM_new[i]
		immediate1b*187, // ->SKIP PAST LIVE CELL 187? TODO
		cond+10, //  else dead cell (skip live)
		comp+3+sram+s1*14+d1*5, // RAM_old[i] | (1<<j), LIVE CELL
		copy+dram+d1*14+s1*3, // RAM_old[i] | (1<<j) -> RAM_new[i]

		//    Now move old i to i-1 aka move RAM 35 to 34
		copy+sram+64+s1*35+dram+32+d1*34,
		comp+7+s1*128+s1+d1*14,
		copy+s1*3+d1*14, // i+=1
		immediate1b*29,//TODO finish loop lines ,  LINE 190
		cond+5+s1*14+d1*128+d1*3,

		// Now move newly computed RAM to Display
		copy+s1*128+d1*7, // x=0 at Reg7
		copy+sram+s1*7+d1*17, // RAM to Disp,
		comp+7+s1*7+d1*128+d1,
		copy+s1*3+d1*7, // x+=1
		immediate1b*193, // LOOP TODO
		cond+5+s1*7+d1*128+d1*3,
		flush,
		comp+7+s1*128+s1+d1*15,
		copy+s1*3+d1*15, // iter+=1
		immediate1b*27,//TODO finish loop frames
		cond+5+s1*15+d1*128+d1*N, 

	};


	hive.add_lines(program);
	int tick_count = 0;
	while (true) {
		// std::cout << "tick " << tick_count++ << std::endl;
		try{
		  hive.tick();}
		catch (std::domain_error& e) {
		  break;}
	}
}
