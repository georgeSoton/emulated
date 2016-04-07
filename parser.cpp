#include "parser.h"
#include "opcodes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <cstdlib>
parser::parser(memoryModule* x)
{
	mem = x;
}

void parser::loadFromFile(const char* file,int16_t startaddress)
{
	int16_t currentaddress = startaddress;
	std::ifstream infile(file);
	if (!infile.good())
	{
		std::cout<<"Bad file specified"<<std::endl;
		exit(0);
	}
	std::string dump;
	std::string p1;
	std::string p2;
	while(std::getline(infile,dump,'%'))
	{
		infile >> p1;
		int16_t opint;
		if (p1 == "NOP")
		{
			opint = NOP;
		}
		else if (p1 == "STD")
		{
			opint = STD;
		}
		else if (p1 == "ADD")
		{
			opint = ADD;
		}
		else if (p1 == "SUB")
		{
			opint = SUB;
		}
		else if (p1 == "MUL")
		{
			opint = MUL;
		}
		else if (p1 == "DIV")
		{
			opint = DIV;
		}
		else if (p1 == "AND")
		{
			opint = AND;
		}
		else if (p1 == "XOR")
		{
			opint = XOR;
		}
		else if (p1 == "ORR")
		{
			opint = ORR;
		}
		else if (p1 == "SPI")
		{
			opint = SPI;
		}
		else if (p1 == "SPD")
		{
			opint = SPD;
		}
		else if (p1 == "JMR")
		{
			opint = JMR;
		}
		else if (p1 == "LDA")
		{
			opint = LDA;
		}
		else if (p1 == "LDR")
		{
			opint = LDR;
		}
		else if (p1 == "IEZ")
		{
			opint = IEZ;
		}
		else if (p1 == "IGZ")
		{
			opint = IGZ;
		}
		else if (p1 == "ILZ")
		{
			opint = ILZ;
		}
		else if (p1 == "IGE")
		{
			opint = IGE;
		}
		else if (p1 == "ILE")
		{
			opint = ILE;
		}
		else if (p1 == "JMA")
		{
			opint = JMA;
		}
		else if (p1 == "STR")
		{
			opint = STR;
		}
		else if (p1 == "END")
		{
			opint = END;
		}
		else
		{
			int memval;
			std::istringstream(p1)>>std::hex>>memval;
			mem->set(currentaddress,memval);
			currentaddress+=1;
			std::getline(infile,dump,'\n');
			continue;
		}
		
		infile >> p2;
		int16_t dataint;
		if (p2 == "SP")
		{
			dataint = SP;
		}
		else if (p2 == "BP")
		{
			dataint = BP;
		}
		else if (p2 == "PC")
		{
			dataint = PC;
		}
		else if (p2 == "OUT")
		{
			dataint = OUT;
		}
		else if (p2 == "U1")
		{
			dataint = U1;
		}
		else if (p2 == "U2")
		{
			dataint = U2;
		}
		else if (p2 == "U3")
		{
			dataint = U3;
		}
		else
		{
			std::istringstream(p2)>>std::hex>>dataint;
		}
		mem->set(currentaddress,LINE(opint,dataint));
		currentaddress+=1;
		std::getline(infile,dump,'\n');
	}
}