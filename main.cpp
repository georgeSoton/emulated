#include "memoryModule.h"
#include "opcodes.h"
#include "parser.h"
#include "alu.h"
#include "fileout.h"
#include <string>
#include <iostream>

std::ofstream outputFile;
int main()
{
	
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
		std::cout<<std::hex<<opcode<<", "<<data<<std::endl;
		MEM.set(PC, MEM.get(PC)+1);	//Increment PC
		if (opcode == END)
		{
			std::cout<<"END"<<std::endl;
			break;
		}
		switch(opcode)
		{
			case NOP:
			std::cout<<"NOP"<<std::endl;
			break;

			case STR:
			std::cout<<"STR"<<std::endl;
			MEM.set(data,ALU.getAcc());
			break;

			case ADD:
			std::cout<<"ADD"<<std::endl;
			ALU.aluAdd(MEM.get(data));
			break;

			case SUB:
			std::cout<<"SUB"<<std::endl;
			ALU.aluSub(MEM.get(data));
			break;

			case MUL:
			std::cout<<"MUL"<<std::endl;
			ALU.aluMul(MEM.get(data));
			break;

			case DIV:
			std::cout<<"DIV"<<std::endl;
			ALU.aluDiv(MEM.get(data));
			break;

			case AND:
			std::cout<<"AND"<<std::endl;
			ALU.aluAnd(MEM.get(data));
			break;

			case XOR:
			std::cout<<"XOR"<<std::endl;
			ALU.aluXor(MEM.get(data));
			break;

			case ORR:
			std::cout<<"ORR"<<std::endl;
			ALU.aluOrr(MEM.get(data));
			break;

			case SPI:
			std::cout<<"SPI"<<std::endl;
			MEM.set(SP,MEM.get(SP)-1);
			break;

			case SPD:
			std::cout<<"SPD"<<std::endl;
			MEM.set(SP,MEM.get(SP)+1);
			break;

			case JMP:
			std::cout<<"JMP"<<std::endl;
			MEM.set(PC,MEM.get(data));
			break;

			case LDA:
			std::cout<<"LDA"<<std::endl;
			ALU.setAcc(MEM.get(ALU.getAcc()));
			break;

			case LDR:
			std::cout<<"LDR"<<std::endl;
			ALU.setAcc(MEM.get(data));
			break;

			case IEZ:
			std::cout<<"IEZ"<<std::endl;
			if (ALU.flagIEZ())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case IGZ:
			std::cout<<"IGZ"<<std::endl;
			if (ALU.flagIGZ())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case ILZ:
			std::cout<<"ILZ"<<std::endl;
			if (ALU.flagILZ())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case IGE:
			std::cout<<"IGE"<<std::endl;
			if (ALU.flagIGE())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case ILE:
			std::cout<<"ILE"<<std::endl;
			if (ALU.flagILE())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case JMD:
			std::cout<<"JMD"<<std::endl;
			MEM.set(PC,data);
			break;

			default:
			std::cout<<"Fell out of opcode case"<<std::endl;
			break;
		}
	}
}