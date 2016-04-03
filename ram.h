#ifndef RAM_H
#define RAM_H
#define RAMLENGTH 0x7EE
#include <stdint.h>
class ram
{
public:
	ram();
	void set(int16_t address, int16_t value);
	int16_t get(int16_t address);
private:
	int16_t memory[RAMLENGTH];
};

#endif