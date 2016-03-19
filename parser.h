#ifndef PARSER_H
#define PARSER_H

#include "memoryModule.h"
#include <string>

class parser
{
public:
	parser(memoryModule* x);
	void loadFromFile(const char* file,int16_t startaddress);
private:
	memoryModule* mem;
	parser();
};

#endif