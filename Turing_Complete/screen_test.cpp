#include <iostream>
#include <thread>
#include <chrono>

int main() {
	std::cout << "\x1b[?1049h\x1b[?25l";
	const int width = 15;//8;
	const int nr_frames = 6; //6;
	int nrs[nr_frames][width] = {
		{127,8,8,8,8,8,8,8,8,8,8,8,8,127,0},
		{0,54,73,73,73,34,20,8,8,0,0,0,0,0,0},
		{129,129,129,129,129,129,129,129,129,129,129,129,129,126,0},
		{0,32767,128,128,16382,8322,8842,9362,10402,8322,8842,9362,10402,8322,14338},
		{288,272,270,32642,8322,5246,1042,1042,1042,1042,2578,2578,4369,8337,16464}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} }; 


	//int nrs[nr_frames][width] = {
	//	{30,33,33,33,33,33,30},
	//	{8,14,8,8,8,8,127},
       	//	{14,17,8,4,2,1,63},
	//	{14,17,16,12,16,17,14},
	//	{1,1,1,5,63,4,4},
       	//	{31,1,1,15,16,16,15},
       	//}; // {0,1,4,63,48, 7};
    	for (int frame = 0; frame < nr_frames; ++frame) {
        	// Move cursor to top-left (row=1, col=1)
        	std::cout << "\x1b[H";
		for (int i = 0; i < width/2; i++) {
			for (int j = 0; j <  width; j++) {
				std::cout << (nrs[frame][2*i] & (1u << j) ? (nrs[frame][2*i+1] & (1u << j) ? "\u2588" : "\u2580") : (nrs[frame][2*i+1] & (1u << j) ? "\u2584" : " "));
			}
			std::cout << "\n";
		}	
	
        	// Flush to make sure it appears immediately
        	std::cout.flush();

        	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    	}

    	// Show cursor again and leave alternate screen buffer
    	std::cout << "\x1b[?25h\x1b[?1049l" << std::endl;
}
