#include "video.h"
#include <cstdlib>
#include <iostream>
video::video()
{
	for(int i=0;i<16;i++)
	{
		lines[i]=0;
	}
	redrawNeeded = false;
}

void video::setline(int line,int16_t value)
{
	lines[line]=value;
	//redrawNeeded = true;
}

void video::draw()
{
	//if (!redrawNeeded)
	//{
	//	return;
	//}
	std::system("cls");
	for(int i=15;i>=0;i--)
	{
		for(int j=15;j>=0;j--)
		{
			if (lines[i]&(1<<j))
			{
				std::cout<<"#";
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