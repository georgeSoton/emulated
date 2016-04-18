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
	rSP = U3;
	rBP = U3;
	rPC = 0;
	rU1 = 0;
	rU2 = 0;
	rU3 = 0;
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
	else if (address == SP)
	{
		rSP = value;
	}
	else if (address == BP)
	{
		rBP = value;
	}
	else if (address == PC)
	{
		rPC = value;
	}
	else if (address == U1)
	{
		rU1 = value;
	}
	else if (address == U2)
	{
		rU2 = value;
	}
	else if (address == U3)
	{
		rU3 = value;
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
	else if (address == SP)
	{
		return rSP;
	}
	else if (address == BP)
	{
		return rBP;
	}
	else if (address == PC)
	{
		return rPC;
	}
	else if (address == U1)
	{
		return rU1;
	}
	else if (address == U2)
	{
		return rU2;
	}
	else if (address == U3)
	{
		return rU3;
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
	if (rBP != U3)
	{
		basepoints.push_back(rBP);
		while(ramModule.get(basepoints.back()) != U3)
		{
			basepoints.push_back(ramModule.get(basepoints.back()));
		}
	}
	std::cout<<" ADDR | NAME| PTRS| VALUE"<<std::endl;	//Header line
	
	for (int16_t i=from;i<=to;i++)						//For each line we're printing out
	{

		std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<i<<" |"<<"-----|";	//Print line number

		if (i == rSP)							//Show where the SP and BP pointers are pointing
		{
			if (rSP==rBP)
			{
				std::cout<<std::setfill('-')<<std::setw(5)<<"SP|BP"<<"|";	//SP and BP at same place
			}
			else
			{
				std::cout<<std::setfill('-')<<std::setw(5)<<"SP"<<"|";
			}
		}
		else if (i == rBP)
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
	std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<U3<<" |"<<std::setfill('-')<<std::setw(5)<<"U3"<<"|"<<"-----|"<<std::setfill('0')<<" "<<"0x"<<std::setw(4)<<rU3<<std::dec<<std::endl;
	std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<U2<<" |"<<std::setfill('-')<<std::setw(5)<<"U2"<<"|"<<"-----|"<<std::setfill('0')<<" "<<"0x"<<std::setw(4)<<rU2<<std::dec<<std::endl;
	std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<U1<<" |"<<std::setfill('-')<<std::setw(5)<<"U1"<<"|"<<"-----|"<<std::setfill('0')<<" "<<"0x"<<std::setw(4)<<rU1<<std::dec<<std::endl;
	std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<PC<<" |"<<std::setfill('-')<<std::setw(5)<<"PC"<<"|"<<"-----|"<<std::setfill('0')<<" "<<"0x"<<std::setw(4)<<rPC<<std::dec<<std::endl;
	std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<BP<<" |"<<std::setfill('-')<<std::setw(5)<<"BP"<<"|"<<"-----|"<<std::setfill('0')<<" "<<"0x"<<std::setw(4)<<rBP<<std::dec<<std::endl;
	std::cout<<std::setfill('0')<<std::hex<<"0x"<<std::setw(3)<<SP<<" |"<<std::setfill('-')<<std::setw(5)<<"SP"<<"|"<<"-----|"<<std::setfill('0')<<" "<<"0x"<<std::setw(4)<<rSP<<std::dec<<std::endl;

}

void memoryModule::setDraw(bool state)	//Turn on/off drawing
{
	drawing = state;
	return;
}