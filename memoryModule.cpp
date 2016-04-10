#include <iostream>
#include "memoryModule.h"
#include <iomanip>
#include "fileout.h"
#include <vector>

memoryModule::memoryModule()
{
	videoModule = video();
	ramModule = ram();
	ramModule.set(SP,U3);	//Set up registers on instantiation
	ramModule.set(BP,U3);
	ramModule.set(PC,0);
	drawing = true;			//Drawing video defaults to true
}

void memoryModule::set(int16_t address, int16_t value)
{
	if ((address > 0x7FF) || (address < 0))
	{
		debugFile<<"Invalid address specified for set: "<<address<<std::endl;	//Out of range debug
		return;
	}
	if (address == FOUT)
	{
		outputFile<<(char)value;					//Outputting to file
	}
	else if ((address > VIDEOBOT) && (address <= VIDEOTOP))	//VIDEO SECTOR
	{
		videoModule.setline(address-(VIDEOBOT+1),value);
	}
	else if (address == VIDEOBOT)
	{
		if (drawing) videoModule.draw();		//Draw if drawing is on when written to this register
	}
	else if (address<RAMLENGTH)
	{
		ramModule.set(address,value);			//Regular memory writing
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
	if (address == FOUT)
	{
		debugFile<<"Tried to read from protected FOUT address"<<std::endl;
	}
	else if ((address >= VIDEOBOT) && (address <= VIDEOTOP)) //VIDEO SECTOR
	{
		debugFile<<"Tried to read from protected VIDEO address"<<std::endl;			//If you're outside of RAM, fail!
	}
	else if (address < RAMLENGTH)
	{
		return ramModule.get(address);		//Else do a regular return
	}
	return 0;
}

void memoryModule::display(int16_t from, int16_t to)
{
	std::vector<int16_t> basepoints;
	basepoints.push_back(U3);
	if (ramModule.get(BP) != U3)
	{
		basepoints.push_back(ramModule.get(BP));
		while(ramModule.get(basepoints.back()) != U3)
		{
			basepoints.push_back(ramModule.get(basepoints.back()));
		}
	}
	std::cout<<" ADDR | NAME| PTRS| VALUE"<<std::endl;	//Header line
	for (int16_t i=from;i<=to;i++)						//For each line we're printing out
	{

		std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<i<<" |";	//Print line number
		switch(i)
		{
			case SP:
			std::cout<<std::setfill('-')<<std::setw(5)<<"SP"<<"|";	//Print register name if there is one
			break;
			case BP:
			std::cout<<std::setfill('-')<<std::setw(5)<<"BP"<<"|";
			break;
			case PC:
			std::cout<<std::setfill('-')<<std::setw(5)<<"PC"<<"|";
			break;
			case FOUT:
			std::cout<<std::setfill('-')<<std::setw(5)<<"FOUT"<<"|";
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


		if (i == ramModule.get(SP))							//Show where the SP and BP pointers are pointing
		{
			if (ramModule.get(SP)==ramModule.get(BP))
			{
				std::cout<<std::setfill('-')<<std::setw(5)<<"SP|BP"<<"|";	//SP and BP at same place
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
			bool matched = false;
			for(int j=0;j<basepoints.size();j++)
			{
				if (basepoints[j] == i) matched = true;
			}
			if (matched)
			{
				std::cout<<std::setfill('x')<<std::setw(5)<<""<<"|";
			}
			else
			{
				std::cout<<std::setfill('-')<<std::setw(5)<<""<<"|";
			}
		}
		std::cout<<std::setfill('0')<<" "<<"0x"<<std::setw(4)<<ramModule.get(i)<<std::dec<<std::endl;	//Print memory contents
	}
}

void memoryModule::setDraw(bool state)	//Turn on/off drawing
{
	drawing = state;
	return;
}