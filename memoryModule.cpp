#include <iostream>
#include "memoryModule.h"
#include <iomanip>
#include "fileout.h"
memoryModule::memoryModule()
{
	video videoModule = video();
	ram ramModule = ram();
	ramModule.set(SP,U3);
	ramModule.set(BP,U3);
	ramModule.set(PC,0);
}

void memoryModule::set(int16_t address, int16_t value)
{
	if ((address > 0x7FF) || (address < 0))
	{
		debugFile<<"Invalid address specified for set: "<<address<<std::endl;
		return;
	}
	if (address == OUT)
	{
		outputFile<<(char)value;
	}
	else if ((address >= VIDEOBOT) && (address <= VIDEOTOP))	//VIDEO SECTOR
	{
		videoModule.setline(address-VIDEOBOT,value);
	}
	else if (address<RAMLENGTH)
	{
		ramModule.set(address,value);
	}
	return;
}

int16_t memoryModule::get(int16_t address)
{
	if ((address > 0x7FF) || (address < 0))
	{
		debugFile<<"Invalid address specified for get: "<<address<<std::endl;
		return 0;
	}
	if (address == OUT)
	{
		debugFile<<"Tried to read from protected OUT address"<<std::endl;
	}
	else if ((address >= VIDEOBOT) && (address <= VIDEOTOP)) //VIDEO SECTOR
	{
		debugFile<<"Tried to read from protected VIDEO address"<<std::endl;
	}
	else if (address < RAMLENGTH)
	{
		return ramModule.get(address);
	}
	return 0;
}

void memoryModule::display(int16_t from, int16_t to)
{
	std::cout<<" ADDR | NAME| PTRS| VALUE"<<std::endl;
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
		if (i == ramModule.get(SP))
		{
			if (ramModule.get(SP)==ramModule.get(BP))
			{
				std::cout<<std::setfill('-')<<std::setw(5)<<"SP|BP"<<"|";
			}
			else
			{
				std::cout<<std::setfill('-')<<std::setw(5)<<"SP"<<"|";
			}
		}
		else if (i == ramModule.get(BP))
		{
			std::cout<<std::setfill('-')<<std::setw(5)<<"BP"<<"|";
		}
		else
		{
			std::cout<<std::setfill('-')<<std::setw(5)<<""<<"|";
		}
		std::cout<<std::setfill('0')<<" "<<"0x"<<std::setw(4)<<ramModule.get(i)<<std::dec<<std::endl;
	}
}

void memoryModule::draw()
{
	videoModule.draw();
	return;
}