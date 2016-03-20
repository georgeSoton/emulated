#include "memoryModule.h"
#include "opcodes.h"
#include "parser.h"
#include "alu.h"
#include "fileout.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

std::ofstream outputFile;
int main(int argc, char *argv[])
{
	std::vector<int16_t> debugpoints;
	bool dodebug	=	false;
	for(int i=1;i<argc;i++)
	{
		std::stringstream ss;
		std::string dump;
		ss<<argv[i];
		std::getline(ss,dump,',');
		if (dump=="-d")
		{
			while(1)
			{
				std::string debugp;
				if(!std::getline(ss,debugp,','))
				{
					break;
				}
				std::stringstream conv;
				int16_t debugint;
				conv << debugp;
				conv >>std::hex>>debugint;
				debugpoints.push_back(debugint);
			}
		}
	}

	memoryModule MEM = memoryModule();
	parser PARSER = parser(&MEM);
	alu ALU = alu();

	std::cout<<"What program would you like to run?"<<std::endl;
	std::cout<<"> ";
	std::string filename;
	std::cin >> filename;

	PARSER.loadFromFile(filename.c_str(),0);
	outputFile.open(("out_"+filename).c_str());
	while(1)
	{
		int16_t currentinstruction = MEM.get(MEM.get(PC));
		uint16_t opcode 	= (uint16_t)currentinstruction>>11;
		int16_t data	= currentinstruction&0x07FF;
		//std::cout<<std::hex<<opcode<<", "<<data<<std::endl;
		int16_t executedline = MEM.get(PC);
		MEM.set(PC, MEM.get(PC)+1);	//Increment PC
		if (opcode == END)
		{
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | END"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			break;
		}
		switch(opcode)
		{
			case NOP:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | NOP"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			break;

			case STA:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | STA"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			MEM.set(data,ALU.getAcc());
			break;

			case ADD:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | ADD"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			ALU.aluAdd(MEM.get(data));
			break;

			case SUB:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | SUB"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			ALU.aluSub(MEM.get(data));
			break;

			case MUL:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | MUL"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			ALU.aluMul(MEM.get(data));
			break;

			case DIV:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | DIV"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			ALU.aluDiv(MEM.get(data));
			break;

			case AND:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | AND"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			ALU.aluAnd(MEM.get(data));
			break;

			case XOR:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | XOR"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			ALU.aluXor(MEM.get(data));
			break;

			case ORR:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | ORR"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			ALU.aluOrr(MEM.get(data));
			break;

			case SPI:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | SPI"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			MEM.set(SP,MEM.get(SP)-1);
			break;

			case SPD:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | SPD"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			MEM.set(SP,MEM.get(SP)+1);
			break;

			case JMP:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | JMP"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			MEM.set(PC,MEM.get(data));
			break;

			case LDA:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | LDA"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			ALU.setAcc(MEM.get(ALU.getAcc()));
			break;

			case LDR:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | LDR"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			ALU.setAcc(MEM.get(data));
			break;

			case IEZ:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | IEZ"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			if (ALU.flagIEZ())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case IGZ:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | IGZ"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			if (ALU.flagIGZ())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case ILZ:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | ILZ"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			if (ALU.flagILZ())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case IGE:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | IGE"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			if (ALU.flagIGE())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case ILE:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | ILE"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			if (ALU.flagILE())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case JMA:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | JMA"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			MEM.set(PC,ALU.getAcc());
			break;

			case STR:
			std::cout<<"Executing line "<<std::hex<<MEM.get(PC)-1<<" | STR"<<std::hex<<", 0x"<<std::setfill('0')<<std::setw(3)<<data<<std::endl;
			MEM.set(MEM.get(data),ALU.getAcc());
			break;

			default:
			std::cout<<"Fell out of opcode case"<<std::endl;
			break;
		}

		for(int i = 0;i<debugpoints.size();i++)
		{
			if (debugpoints[i] == executedline)
			{
				dodebug = true;
			}
		}

		if (dodebug)
		{
			std::cout<<"------------------------------------"<<std::endl;
			std::cout<<"Accumulator is "<<ALU.getAcc()<<std::endl;
			MEM.display(0x07EF,0x07FF);
			std::cout<<"------------------------------------"<<std::endl;
			char a;
			std::cout<<"n -> next line\tother key -> next breakpoint"<<std::endl;
			std::fflush(stdin);
			std::cin.get(a);
			if (a != 'n')
			{
				dodebug = false;
			}
		}
		
	}
}