#include <iostream>
#include "memoryModule.h"
#include <iomanip>
#include "fileout.h"
memoryModule::memoryModule()
{
	for(int i=0;i<=0x7FF;i++)
	{
		memory[i]=0;
	}
	memory[SP] = 	0x7FC;
	memory[BP] = 	0x7FC;
	memory[PC] = 	0x000;
}

void memoryModule::set(int16_t address, int16_t value)
{
	if ((address > 0x7FF) || (address < 0))
	{
		std::cout<<"Invalid address specified for set: "<<address<<std::endl;
		return;
	}
	if (address == OUT)
	{
		outputFile<<(char)value;
	}
	memory[address] = value;
	return;
}

int16_t memoryModule::get(int16_t address)
{
	if ((address > 0x7FF) || (address < 0))
	{
		std::cout<<"Invalid address specified for get: "<<address<<std::endl;
		return 0;
	}
	if (address == OUT)
	{
		std::cout<<"Tried to read from protected OUT address"<<std::endl;
	}
	return memory[address];
}

void memoryModule::display(int16_t from, int16_t to)
{
	for (int16_t i=from;i<=to;i++)
	{
		std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<i<<"\t|\t"<<"0x"<<std::setw(4)<<memory[i]<<std::dec<<std::endl;
	}
}