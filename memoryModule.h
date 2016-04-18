#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "ram.h"
#include "video.h"

#define FOUT 	0x7FF

#define VIDEOTOP 0x7FE
#define VIDEOBOT 0x7EE	//Bottommost bit sets a draw when written

#define SP 		0x7ED
#define BP 		0x7EC
#define PC 		0x7EB

#define U1		0x7EA
#define U2		0x7E9
#define U3		0x7E8



class memoryModule
{
public:
	memoryModule();
	void set(int16_t address, int16_t value);
	int16_t get(int16_t address);
	void display(int16_t from, int16_t to);
	void setDraw(bool state);
private:
	int16_t rSP,rBP,rPC,rU1,rU2,rU3;	//Privileged registers
	ram ramModule;
	video videoModule;
	bool drawing;
};

#endif