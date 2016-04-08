#include "video.h"
#include <cstdlib>
#include <iostream>
video::video()
{
	for(int i=0;i<16;i++)	//Initially all 0
	{
		lines[i]=0;
	}
}

void video::setline(int line,int16_t value)
{
	lines[line]=value;
}

void video::draw()
{
	std::system("cls");		//Clear output THIS IS WINDOWS SPECIFIC
	for(int i=15;i>=0;i--)	//Iterate backwards through lines
	{
		for(int j=15;j>=0;j--)	//Iterate backwards through bits
		{
			if (lines[i]&(1<<j))
			{
				std::cout<<"#";		//Print # for 1, space for 0
			}
			else
			{
				std::cout<<"-";
			}
		}
		std::cout<<std::endl;
	}
	return;
}