#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define SP 0x7FF
#define BP 0x7FE
#define PC 0x7FD
#define OUT 0x7FC


class memoryModule
{
public:
	memoryModule();
	void set(int16_t address, int16_t value);
	int16_t get(int16_t address);
	void display(int16_t from, int16_t to);
private:
	int16_t memory[0x7FF];
};

#endif