#include "parser.h"
#include "opcodes.h"
#include <iostream>
#include <fstream>
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
	std::string comment;
	std::string op;
	std::string data;
	while(std::getline(infile,comment,'*'))
	{
		std::getline(infile,op,',');
		std::getline(infile,data);
		int16_t opint;
		if (op == "NOP")
		{
			opint = NOP;
		}
		else if (op == "STA")
		{
			opint = STA;
		}
		else if (op == "ADD")
		{
			opint = ADD;
		}
		else if (op == "SUB")
		{
			opint = SUB;
		}
		else if (op == "MUL")
		{
			opint = MUL;
		}
		else if (op == "DIV")
		{
			opint = DIV;
		}
		else if (op == "AND")
		{
			opint = AND;
		}
		else if (op == "XOR")
		{
			opint = XOR;
		}
		else if (op == "ORR")
		{
			opint = ORR;
		}
		else if (op == "SPI")
		{
			opint = SPI;
		}
		else if (op == "SPD")
		{
			opint = SPD;
		}
		else if (op == "JMP")
		{
			opint = JMP;
		}
		else if (op == "LDA")
		{
			opint = LDA;
		}
		else if (op == "LDR")
		{
			opint = LDR;
		}
		else if (op == "IEZ")
		{
			opint = IEZ;
		}
		else if (op == "IGZ")
		{
			opint = IGZ;
		}
		else if (op == "ILZ")
		{
			opint = ILZ;
		}
		else if (op == "IGE")
		{
			opint = IGE;
		}
		else if (op == "ILE")
		{
			opint = ILE;
		}
		else if (op == "JMD")
		{
			opint = JMD;
		}
		else if (op == "STR")
		{
			opint = STR;
		}
		else if (op == "END")
		{
			opint = END;
		}
		else
		{
			mem->set(currentaddress,strtol(op.c_str(),0,16));
			currentaddress+=1;
			continue;
		}
		

		int16_t dataint;
		if (data == "SP")
		{
			dataint = SP;
		}
		else if (data == "BP")
		{
			dataint = BP;
		}
		else if (data == "PC")
		{
			dataint = PC;
		}
		else if (data == "OUT")
		{
			dataint = OUT;
		}
		else if (data == "U1")
		{
			dataint = U1;
		}
		else
		{
			dataint = strtol(data.c_str(),0,16);
		}
		mem->set(currentaddress,LINE(opint,dataint));
		currentaddress+=1;
	}
}