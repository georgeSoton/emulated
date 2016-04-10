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
#include <windows.h>

std::ofstream outputFile;
std::ofstream debugFile;		//Extern'd output files

int main(int argc, char *argv[])
{
	std::vector<int16_t> debugpoints;	//Holds the breakpoints
	bool dodebug	=	false;			//Loop variable that decides if we should go into debug printing
	int debuglen	=	0xF;			//How far down the memory to print
	bool printline  =	false;			//Whether to print out each line
	bool video		=	true;			//Whether to print video

	for(int i=1;i<argc;i++)				//For each cmd line argument
	{
		std::stringstream ss;			//Stream holder for the argument
		std::string dump;				//Place to drop stuff
		ss<<argv[i];
		std::getline(ss,dump,',');		//Load up until the first comma
		if (dump=="-bp")				//If it's the breakpoint argument
		{
			video = false;				//Turn off video output (cos we're debugging)
			while(1)					//Loop through points
			{
				std::string debugp;					//String to hold debugpoints
				if(!std::getline(ss,debugp,','))	//See if there is another item in the list
				{
					break;
				}
				int16_t debugint;
				std::stringstream(debugp)>>std::hex>>debugint;	//Load that debugpoint into a variable and
				debugpoints.push_back(debugint);				//Add to list
			}
		}
		else if (dump=="-len")					//If length argument
		{
				std::string val;
				if(!std::getline(ss,val,' '))	//Get rest of argument
				{
					break;
				}
				int16_t valint;
				std::stringstream(val)>>std::hex>>valint;	//Load into debuglen
				debuglen = valint;
		}
		else if (dump=="-lines")			//If lines argument
		{
			video = false;					//Turn on line reporting, turn off video
			printline = true;
		}
		else
		{
			std::cout<<std::endl;			//Help
			std::cout<<"\t-bp,0,1,2,3 | Get breakpoints on those lines (in hex)"<<std::endl;
			std::cout<<"\t-len,0xF    | Length at end of memory to see"<<std::endl;
			std::cout<<"\t-lines      | View all lines as they run"<<std::endl;
			std::cout<<"\t Having lines displayed or breakpoints turns off video"<<std::endl;
			return 0;
		}
	}
	std::cout<<"What program would you like to run?"<<std::endl;
	std::cout<<"> ";
	std::string filename;
	std::cin >> filename;
	outputFile.open(("out_"+filename).c_str());
	debugFile.open(("debug_"+filename).c_str());	//Open output filestreams

	memoryModule MEM = memoryModule();	//Initialise modules
	MEM.setDraw(video);					//Turn on/off video report
	parser PARSER = parser(&MEM);
	alu ALU = alu();
	PARSER.loadFromFile(filename.c_str(),0);	//Load from text into memory
	while(1)
	{
		Sleep(1);
		int16_t currentinstruction = MEM.get(MEM.get(PC));	//Fetch instruction and separate into parts
		uint16_t opcode 	= (uint16_t)currentinstruction>>11;
		int16_t data	= currentinstruction&0x07FF;
		int16_t executedline = MEM.get(PC);					//Save current line for the sake of debug
		MEM.set(PC, MEM.get(PC)+1);							//Increment PC

		//All operations
		if (opcode == END)
		{
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | END";
			}
			break;
		}
		switch(opcode)
		{
			case NOP:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | NOP";
			}
			break;

			case STD:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | STD";
			}
			MEM.set(data,ALU.getAcc());
			break;

			case ADD:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | ADD";
			}
			ALU.aluAdd(MEM.get(data));
			break;

			case SUB:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | SUB";
			}
			ALU.aluSub(MEM.get(data));
			break;

			case MUL:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | MUL";
			}
			ALU.aluMul(MEM.get(data));
			break;

			case DIV:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | DIV";
			}
			ALU.aluDiv(MEM.get(data));
			break;

			case AND:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | AND";
			}
			ALU.aluAnd(MEM.get(data));
			break;

			case XOR:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | XOR";
			}
			ALU.aluXor(MEM.get(data));
			break;

			case ORR:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | ORR";
			}
			ALU.aluOrr(MEM.get(data));
			break;

			case SPI:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | SPI";
			}
			MEM.set(SP,MEM.get(SP)-1);
			break;

			case SPD:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | SPD";
			}
			MEM.set(SP,MEM.get(SP)+1);
			break;

			case JMR:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | JMR";
			}
			MEM.set(PC,MEM.get(data));
			break;

			case LDA:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | LDA";
			}
			ALU.setAcc(MEM.get(ALU.getAcc()));
			break;

			case LDR:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | LDR";
			}
			ALU.setAcc(MEM.get(data));
			break;

			case IEZ:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | IEZ";
			}
			if (ALU.flagIEZ())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case IGZ:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | IGZ";
			}
			if (ALU.flagIGZ())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case ILZ:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | ILZ";
			}
			if (ALU.flagILZ())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case IGE:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | IGE";
			}
			if (ALU.flagIGE())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case ILE:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | ILE";
			}
			if (ALU.flagILE())
			{
				MEM.set(PC,MEM.get(data));
			}
			break;

			case JMA:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | JMA";
			}
			MEM.set(PC,ALU.getAcc());
			break;

			case STR:
			if (printline)
			{
				std::cout<<"Executing line "<<std::hex<<"0x"<<std::setfill('0')<<std::setw(3)<<MEM.get(PC)-1<<" | STR";
			}
			MEM.set(MEM.get(data),ALU.getAcc());
			break;

			default:
			std::cout<<"Fell out of opcode case"<<std::endl;
			break;
		}
		if(printline)
		{
			switch(data)
			{
				case SP:
				std::cout<<", SP"<<std::endl;
				break;

				case BP:
				std::cout<<", BP"<<std::endl;
				break;

				case PC:
				std::cout<<", PC"<<std::endl;
				break;

				case U1:
				std::cout<<", U1"<<std::endl;
				break;

				case U2:
				std::cout<<", U2"<<std::endl;
				break;

				case U3:
				std::cout<<", U3"<<std::endl;
				break;

				case FOUT:
				std::cout<<", FOUT"<<std::endl;
				break;

				default:
				std::cout<<", 0x"<<std::hex<<std::setw(3)<<data<<std::endl;
				break;
			}
		}

		for(int i = 0;i<debugpoints.size();i++)	//If we are on a debug line, ensure dodebug is true
		{
			if (debugpoints[i] == executedline)
			{
				dodebug = true;
			}
		}

		if (dodebug)			//If we need to output debug
		{
			//Pretty debug message!
			std::cout<<"------------------------------------"<<std::endl;
			std::cout<<"Line "<<executedline<<std::endl;
			MEM.display(RAMLENGTH-1-debuglen,RAMLENGTH-1);
			std::cout<<"ACCUMULATOR ------| 0x"<<std::hex<<std::setfill('0')<<std::setw(4)<<ALU.getAcc()<<std::endl;
			std::cout<<"------------------------------------"<<std::endl;
			char a;
			std::cout<<"[N] NEXT LINE   |   [OTHER] NEXT BREAKPOINT"<<std::endl<<std::endl;
			std::fflush(stdin);
			std::cin.get(a);		//Offer the chance to advance to the next breakpoint or go line by line
			if ((a != 'n') && (a != 'N'))
			{
				dodebug = false;	//Keep dodebug on the next line only if we asked so
			}
		}
	}
}