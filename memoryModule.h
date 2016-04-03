#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "ram.h"
#include "video.h"

#define OUT 	0x7FF

#define VIDEOTOP 0x7FE
#define VIDEOBOT 0x7EF

#define SP 		0x7EE
#define BP 		0x7ED
#define PC 		0x7EC

#define U1		0x7EB
#define U2		0x7EA
#define U3		0x7E9


class memoryModule
{
public:
	memoryModule();
	void set(int16_t address, int16_t value);
	int16_t get(int16_t address);
	void display(int16_t from, int16_t to);
	void draw();
private:
	ram ramModule;
	video videoModule;
};

#endif