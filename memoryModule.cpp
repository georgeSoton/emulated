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
	memory[SP] = 	0x7F9;
	memory[BP] = 	0x7F9;
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

		std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<i<<" |";
		switch(i)
		{
			case SP:
			std::cout<<std::setfill('-')<<std::setw(5)<<"SP"<<"|";
			break;
			case BP:
			std::cout<<std::setfill('-')<<std::setw(5)<<"BP"<<"|";
			break;
			case PC:
			std::cout<<std::setfill('-')<<std::setw(5)<<"PC"<<"|";
			break;
			case OUT:
			std::cout<<std::setfill('-')<<std::setw(5)<<"OUT"<<"|";
			break;
			case U1:
			std::cout<<std::setfill('-')<<std::setw(5)<<"U1"<<"|";
			break;
			case U2:
			std::cout<<std::setfill('-')<<std::setw(5)<<"U2"<<"|";
			break;
			case U3:
			std::cout<<std::setfill('-')<<std::setw(5)<<"U3"<<"|";
			break;
			default:
				std::cout<<std::setfill('-')<<std::setw(5)<<""<<"|";
			break;
		}
		if (i == memory[SP])
		{
			if (memory[SP]==memory[BP])
			{
				std::cout<<std::setfill('-')<<std::setw(5)<<"SP|BP"<<"|";
			}
			else
			{
				std::cout<<std::setfill('-')<<std::setw(5)<<"SP"<<"|";
			}
		}
		else if (i == memory[BP])
		{
			std::cout<<std::setfill('-')<<std::setw(5)<<"BP"<<"|";
		}
		else
		{
			std::cout<<std::setfill('-')<<std::setw(5)<<""<<"|";
		}
		std::cout<<std::setfill('0')<<" "<<"0x"<<std::setw(4)<<memory[i]<<std::dec<<std::endl;
	}
}